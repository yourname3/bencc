#include "compiler.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "error.h"

void
compiler_init(struct compiler *compiler) {

}

void
compiler_destroy(struct compiler *compiler) {

}

void compiler_compile_file_handle(struct compiler *compiler, FILE *file) {
    struct lexer lexer;
    lex_init(&lexer, file);

    // Initial lexer driver
    for(;;) {
        struct token tok = lex(&lexer);
        if(tok.type == T_EOF) {
            break;
        }
        printf("'%s'; ", tok.str.in);
    }

    lex_destroy(&lexer);
}

void
compiler_compile_file_path(struct compiler *compiler, const char *path) {
    FILE *the_file = fopen(path, "r");
    if(!the_file) {
        error("Could not open input file '%s': %s\n", path, strerror(errno));
    }

    compiler_compile_file_handle(compiler, the_file);

    fclose(the_file);
}