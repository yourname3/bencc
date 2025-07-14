#include "compiler.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "error.h"

void
compiler_init(struct compiler *compiler) {

}

void
compiler_compile_file_path(struct compiler *compiler, const char *path) {
    FILE *the_file = fopen(path, "r");
    if(!the_file) {
        error("Could not open input file '%s': %s\n", path, strerror(errno));
    }

    struct lexer lexer;
    lex_init(&lexer, the_file);

    // Initial lexer driver
    for(;;) {
        lex(&lexer);
    }

    lex_destroy(&lexer);
    fclose(the_file);
}