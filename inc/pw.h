#ifndef PW_H
#define PW_H
#include <stdint.h>

struct arguments {
    char *args[2];
    int verbose;
};

enum pw_result_t{
    PW_SUCCESS,
    PW_FAILED_TO_ALLOCATE_MEMORY,
    PW_MEMORY_FAULT,
    PW_INTERRUPTED,
    PW_NO_KERNEL_SUPPORT,
    PW_NOT_A_VALID_ARGUMENT
};

struct password_result_t {
    enum pw_result_t result;
    char *pw;
};

enum input_alphabet_t {
    ALPHANUMERIC_W_SYMBOLS,
    ALPHANUMERIC,
    LATIN_CHARACTERS,
    SYMBOLS,
    DIGITS
};

struct password_options {
    enum input_alphabet_t alphabet;
    uint32_t password_length;
};

void
generate_password(struct arguments *arugments, struct password_result_t *result);

void
print_error_msg(struct password_result_t *result);

#endif