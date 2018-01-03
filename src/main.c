#include <argp.h>
#include <stdio.h>
#include <string.h>
#include "file_cache_v5.h"


static char doc[] = "ngx_file_cache_dumper -- dumps info from nginx's cache file";

static char args_doc[] = "file";

static struct argp_option options[] =
{
    {"verbose", 'v', 0, 0, "Complete output"},
    {"file",    'f', "FILE", 0, "Cache file to read"},
    { 0 }
};

struct arguments
{
  int       verbose;
  char *    input_file;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct arguments * arguments = state->input;
    switch (key)
    {
        case 'v':
            arguments->verbose = 1;
            break;
        case 'f':
            arguments->input_file = arg;
            break;
        case ARGP_KEY_END:
            if (strlen(arguments->input_file) < 2)
            {
                argp_usage (state);
                return ARGP_ERR_UNKNOWN;
            }
            break;
        case ARGP_KEY_NO_ARGS:
            return ARGP_ERR_UNKNOWN;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char **argv)
{
    struct arguments arguments;

    arguments.verbose = 0;
    arguments.input_file = "-";
    FILE *f;
    ngx_http_file_cache_header_v5_t dest;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    dest = read_v5(arguments.input_file);
    print_v5(dest);

    return 0;
}
