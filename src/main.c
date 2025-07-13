#include <stdio.h>

int
main(int argc, char **argv) {
    const char *progname = "bencc";
    if(argc > 0) progname = argv[0];

    printf("usage: %s [--lex|--parse|--codegen] <input.c>\n", progname);
    return 0;
}