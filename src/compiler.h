#ifndef BENCC_COMPILER_H
#define BENCC_COMPILER_H

#include <stdio.h>

#include "lex.h"

struct compiler {

};

void compiler_init(struct compiler *compiler);
void compiler_destroy(struct compiler *compiler);
void compiler_compile_file_path(struct compiler *compiler, const char *path);
void compiler_compile_file_handle(struct compiler *compiler, FILE *file);

#endif