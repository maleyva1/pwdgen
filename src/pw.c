#include <malloc.h>
#include <sys/random.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pw.h"

#define MAX_BUFFER_LEN 255 

uint32_t idx = 0;

/* Function Prototypes  */
bool 
is_in_range_of(enum input_alphabet_t alphabet, uint8_t index);

void
pw_copy(struct password_options pw_opt, char *gen, char *tmp, bool  *flag);

bool
in_digits(uint8_t index);
bool
in_latin(uint8_t index);
bool
in_symbols(uint8_t index);
/*  ------------------- */

/*
    Generates a random password.
    @params     arguments:      A structure containing the arguments
*/
void
generate_password(struct arguments *arguments, struct password_result_t *result)
{
    struct password_options pw_opt;
    char *generated_pw;

    size_t len = strlen(arguments->args[0]);

    if ((strncmp(arguments->args[0], "asd", 3) == 0) && len == 3) {
        pw_opt.alphabet = ALPHANUMERIC_W_SYMBOLS;
    } else if (strncmp(arguments->args[0], "a", 1) == 0 && len == 1) {
        pw_opt.alphabet = ALPHANUMERIC;
    } else if(strncmp(arguments->args[0], "l", 1) ==0 && len == 1) {
        pw_opt.alphabet = LATIN_CHARACTERS;
    } else if(strncmp(arguments->args[0], "s", 1) == 0 && len == 1) {
        pw_opt.alphabet = SYMBOLS;
    } else if (strncmp(arguments->args[0], "d", 1) == 0 && len == 1) {
        pw_opt.alphabet = DIGITS;
    } else {
        fprintf(stderr, "%s is not a valid alphabet set\n", arguments->args[0]);
        fprintf(stderr, "Use 'a', 's', 'l', 'd', or 'asd'.\n");
        result->result = PW_NOT_A_VALID_ARGUMENT;
        return;
    }

    pw_opt.password_length = atoi(arguments->args[1]);
    if (pw_opt.password_length <= 0) {
        fprintf(stderr, "Not a valid length\n");
        result->result = PW_NOT_A_VALID_ARGUMENT;
        return;
    }

    char *pw = malloc(pw_opt.password_length * sizeof(char));
    if (!pw) {
        result->result = PW_FAILED_TO_ALLOCATE_MEMORY;
        return;
    }

    char *buffer = malloc(MAX_BUFFER_LEN * sizeof(char));
    if (!buffer) {
        free(pw);
        result->result = PW_FAILED_TO_ALLOCATE_MEMORY;
        return;
    }

    ssize_t randomResult = 0;
    bool uninit = true;

    while(uninit) {
        randomResult = getrandom(buffer, MAX_BUFFER_LEN, GRND_NONBLOCK);
        switch(randomResult) {
            case EFAULT:
                result->result = PW_MEMORY_FAULT;
                return;
            case ENOSYS:
                result->result = PW_NO_KERNEL_SUPPORT;
                return;
            case EINTR:
                /* Fallthrough: Don't care for this case. Try again*/
                randomResult = -1;
            default:
                break;
        }
        if (randomResult != -1) {
            pw_copy(pw_opt, pw, buffer, &uninit);
        }
    }

    free(buffer);
    generated_pw = (char *) calloc(pw_opt.password_length + 1, sizeof(char));
    memcpy(generated_pw, pw, pw_opt.password_length);
    free(pw);

    result->pw = generated_pw;
    result->result = PW_SUCCESS;
}

void
print_error_msg(struct password_result_t *result)
{
    switch(result->result) {
    case PW_FAILED_TO_ALLOCATE_MEMORY:
        fprintf(stdout, "Unable to allocate memory for password to be generated.\n");
        break;
    case PW_MEMORY_FAULT:
        fprintf(stdout, "Memory fault occured.\n");
        break;
    case PW_NO_KERNEL_SUPPORT:
        fprintf(stdout, "No support for generating passwords on this machine.\n");
        break;
    case PW_SUCCESS:
        if (result->pw)
            fprintf(stdout, "%s\n", result->pw);
        break;
    case PW_INTERRUPTED:
        /* Fallthrough */
    default:
        break;
    }

    if (result->result == PW_SUCCESS)
        free(result->pw);
}

/* ------- Private functions --------------- */
bool
is_in_range_of(enum input_alphabet_t alphabet, uint8_t index)
{
    bool rValue = false;
    switch(alphabet) {
    case ALPHANUMERIC_W_SYMBOLS:
        rValue = (in_symbols(index) || in_digits(index) || in_latin(index));
        break;
    case ALPHANUMERIC:
        rValue = (in_digits(index) || in_latin(index));
        break;
    case LATIN_CHARACTERS:
        rValue = in_latin(index);
        break;
    case SYMBOLS:
        rValue = in_symbols(index);
        break;
    case DIGITS:
        rValue = in_digits(index);
        break;
    default:
        break;
    }
    return rValue;
}

bool
in_digits(uint8_t index)
{
    if (('0' <= index) && (index <= '9')) {
        return true;
    }
    return false;
}

bool
in_latin(uint8_t index)
{
    if ((('a' <= index) && (index <= 'z')) ||
        (('A' <= index) && (index <= 'Z'))) {
            return true;
    }
    return false;
}

bool
in_symbols(uint8_t index)
{
    if ((('!' <= index) && (index <= '/')) || 
       ((':' <= index) && (index <= '@')) ||
       (('[' <= index) && (index <= '`')) ||
       (('{' <= index) && (index <= '~'))) {
           return true;
    }
    return false;
}

/*
    Copy all elements of the random vector `tmp` to `gen` if
    element at index I is within the range of characters as
    specified for the options.

    @params     ops:    The paramaters the user passed.
    @params     gen:    The output buffer.
    @params     tmp:    The random vector.
    @params     flag:   Controls outer calling loop
*/
void
pw_copy(struct password_options opts, char *gen, char *tmp, bool *flag)
{
    for(uint32_t i = 0; i < opts.password_length && idx < opts.password_length; i++) {
        if (is_in_range_of(opts.alphabet, tmp[i])) {
            gen[idx] = tmp[i];
            idx++;
        } 
    }

    if (idx == opts.password_length) {
        *flag = false;
    }
}
