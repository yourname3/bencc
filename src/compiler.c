#include "compiler.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "error.h"
#include "parser.h"
#include "pretty_print.h"

#include "backend/x86/x86.h"

void
compiler_init(struct compiler *compiler) {

}

void
compiler_destroy(struct compiler *compiler) {

}

void compiler_compile_file_handle(struct compiler *compiler, FILE *file) {
    struct parser p;
    parse_init(&p, file);

    struct program *prog = parse(&p);

    //pretty_print(prog);
    struct x86_program *x86 = compile_to_x86(prog);
    emit_text_x86(stdout, x86);

    parse_destroy(&p);
}

void
compiler_compile_file_path(struct compiler *compiler, const char *path) {
    FILE *the_file = fopen(path, "r");
    if(!the_file) {
        error("Could not open input file '%s': %s", path, strerror(errno));
    }

    compiler_compile_file_handle(compiler, the_file);

    fclose(the_file);
}