#ifndef BENCC_LEX_H
#define BENCC_LEX_H

#include <stdio.h>
#include <stddef.h>

#include "intern.h"

enum token_type {
    T_EOF,
    T_NUM,
    T_ID,

    T_LPAREN,
    T_RPAREN,
    T_LBRACE,
    T_RBRACE,

    T_ERROR,
};

struct token {
    enum token_type type;
    struct str str;
};

struct lexer {
    FILE *input;
    int peek;

    char *buf;
    size_t buf_size;
    size_t buf_len;

    struct compiler *compiler;
};

void lex_init(struct lexer *l, FILE *input);
void lex_destroy(struct lexer *l);
struct token lex(struct lexer *l);

#endif