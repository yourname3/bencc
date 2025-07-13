#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "options.h"

static const char *progname = "bencc";

static
_Noreturn
void
usage() {
    printf("usage: %s [--lex|--parse|--codegen] <input.c>\n", progname);
    exit(0);
}

int
main(int argc, char **argv) {
    if(argc > 0) progname = argv[0];

    if(argc < 2) {
        usage();
    }

    int c_file_idx = 1;

    if(!strcmp(argv[1], "--lex")) {
        options.stage = STAGE_LEX;
        c_file_idx += 1;
    }
    else if(!strcmp(argv[1], "--parse")) {
        options.stage = STAGE_PARSE;
        c_file_idx += 1;
    }
    else if(!strcmp(argv[1], "--codegen")) {
        options.stage = STAGE_CODEGEN;
        c_file_idx += 1;
    }

    if(c_file_idx >= argc) {
        usage();
    }

    FILE *input_file = fopen(argv[c_file_idx], "r");
    if(!input_file) {
        printf("Error: Could not open input file '%s': %s\n", argv[c_file_idx], strerror(errno));
        return 1;
    }

    int next = EOF;
    while((next = fgetc(input_file)) != EOF) {
        printf("%c", next);
    }

    fclose(input_file);

    return 0;
}