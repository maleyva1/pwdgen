#include <argp.h>
#include <string.h>
#include <stdio.h>
#include "pw.h"

const char *argp_program_version = 
"pwdgen 1.0";
const char *argp_program_bug_address = 
"<mark@leyva.me>";
static const char doc[] = 
"Random Password Generator -- A small random ASCII password generator.\n\
ALPHABET is either 'a', 's', 'l', 'd', or 'asd'\n\
LENGTH is a positive integer specifying the length of the generated password\n";
static const char args_doc[] = 
"ALPHABET LENGTH";

static error_t
parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;

    switch(key) {
    case ARGP_KEY_ARG:
        if (state->arg_num >= 2) {
            argp_usage(state);
        }
        arguments->args[state->arg_num] = arg;
        break;
    case ARGP_KEY_END:
        if (state->arg_num < 2) {
            argp_usage(state);
        }
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

static struct argp arg_p = { 0, parse_opt, args_doc, doc };

int main(int argc, char *argv[]) {
    struct arguments arguments;

    /* Default Values */
    arguments.verbose = 0;
    argp_parse(&arg_p, argc, argv, 0, 0, &arguments);

    // Generate password
    struct password_result_t result;
    memset(&result, 0, sizeof(result));
    result.result = PW_FAILURE;

    generate_password(&arguments, &result);

    // Print result
    print_error_msg(&result);
}
