#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "options.h"
#include "compiler.h"

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

    struct compiler compiler;
    compiler_init(&compiler);

    compiler_compile_file_path(&compiler, argv[c_file_idx]);

    return 0;
}