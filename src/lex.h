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

    T_SEMICOLON,

    T_AUTO,
    T_BREAK,
    T_CASE,
    T_CHAR,
    T_CONST,
    T_CONTINUE,
    T_DEFAULT,
    T_DO,
    T_DOUBLE,
    T_ELSE,
    T_ENUM,
    T_EXTERN,
    T_FLOAT,
    T_FOR,
    T_GOTO,
    T_IF,
    T_INLINE,
    T_INT,
    T_LONG,
    T_REGISTER, // probably noop for us
    T_RESTRICT, // probably noop for us
    T_RETURN,
    T_SHORT,
    T_SIGNED,
    T_SIZEOF,
    T_STATIC,
    T_STRUCT,
    T_SWITCH,
    T_TYPEDEF,
    T_TYPEOF,
    T_TYPEOF_UNQUAL,
    T_UNION,
    T_UNSIGNED,
    T_VOID,
    T_VOLATILE,
    T_WHILE,
    T_ALIGNAS,
    T_ALIGNOF,
    T_ATOMIC, // unlikely (?) to happen
    T_BOOL,
    T_COMPLEX, // unlikely to happen
    T_GENERIC,
    T_IMAGINARY, // unlikely to happen
    T_NORETURN, // probably noop for us
    T_STATIC_ASSERT,
    T_THREAD_LOCAL, // unlikely to happen

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