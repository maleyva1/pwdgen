#include <argp.h>
#include <string.h>
#include <stdio.h>
#include "pw.h"

const char *argp_program_version = "pwdgen 1.0";
const char *argp_program_bug_address = "<leyva.mark@yahoo.com>";
static const char doc[] = "Random Password Generator -- A small random ASCII password generator.";
static const char args_doc[] = "<alphanumeric|digits|symbols|alphanumeric_w_symbolds> pw_length";

static struct argp_option options[] = {
    {0}
};

static error_t
parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;

    switch(key) {
        break;
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

static struct argp arg_p = { options, parse_opt, args_doc, doc };

int main(int argc, char *argv[]) {
    struct arguments arguments;

    /* Default Values */
    arguments.verbose = 0;
    argp_parse(&arg_p, argc, argv, 0, 0, &arguments);

    // Generate password
    struct password_result_t result;
    memset(&result, 0, sizeof(result));

    generate_password(&arguments, &result);

    // Print result
    print_error_msg(&result);
}