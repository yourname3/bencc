#include "lex.h"

#include <stdio.h>
#include <stdbool.h>

#include "alloc.h"
#include "intern.h"
#include "error.h"

static void
resize_buffer(struct lexer *l, size_t new_size) {
    l->buf_size = new_size;
    l->buf = reallocate(l->buf, new_size);
}

void
lex_init(struct lexer *l, FILE *input) {
    if(!l) return;

    l->input = input;
    l->next = ' ';

    l->buf_size = 0;
    l->buf_len = 0;
    l->buf = NULL;

    resize_buffer(l, 256);
}

void
lex_destroy(struct lexer *l) {
    if(!l) return;

    free(l->buf);
    l->buf = NULL;

    l->buf_size = 0;
    l->buf_len = 0;
}

static bool
is_whitespace(int what) {
    return what == ' ' || what == '\t' || what == '\r' || what == '\n';
}

static bool
is_num(int c) {
    return c >= '0' && c <= '9';
}

static bool
is_alpha(int c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static void
advance(struct lexer *l) {
    l->next = fgetc(l->input);
}

static void
advance_push(struct lexer *l) {
    advance(l);
}

static void
begin(struct lexer *l) {
    l->buf_size = 0;
}

static struct token
token(struct lexer *l, enum token_type type) {
    return (struct token){
        .type = type,
        .str = intern(l->buf)
    };
}  

static struct token
number(struct lexer *l) {
    
    while(is_num(l->next)) {
        advance_push(l);
    }
    return token(l, T_NUM);
}

struct token
lex(struct lexer *l) {
    while(is_whitespace(l->next)) { advance(l); }

    begin(l);

    if(is_num(l->next)) {
        return number(l);
    }

    switch(l->next) {
        case EOF: return token(l, T_EOF);
        case '(': return token(l, T_LPAREN);
        case ')': return token(l, T_RPAREN);
        case '{': return token(l, T_LBRACE);
        case '}': return token(l, T_RBRACE);
        default:
            error("Invalid token: Unexpected character '%c'.\n", l->next);
    }
}




