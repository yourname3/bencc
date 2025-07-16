#include "lex.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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
    l->peek = ' ';

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

static int
advance(struct lexer *l) {
    int curr = l->peek;
    l->peek = fgetc(l->input);

    if(curr >= 0 && curr <= 255) {
        if(l->buf_len + 2 > l->buf_size) {
            resize_buffer(l, (l->buf_size ? l->buf_size : 8) * 2);
        }
        l->buf[l->buf_len++] = (char)curr;
    }

    return curr;
}

static void
begin(struct lexer *l) {
    l->buf_len = 0;
}

static struct token
token(struct lexer *l, enum token_type type) {
    l->buf[l->buf_len] = '\0';
    return (struct token){
        .type = type,
        .str = intern(l->buf)
    };
}  

static struct token
number(struct lexer *l) {
    while(is_num(l->peek)) {
        advance(l);
    }
    return token(l, T_NUM);
}

static struct token
identifier(struct lexer *l) {
    while(is_num(l->peek) || is_alpha(l->peek)) {
        advance(l);
    }

    enum token_type ty = T_ID;

    // TEMPORARY:
    // Set the nul terminator now, because we're using strcmp.
    l->buf[l->buf_len] = '\0';

    // Trie for computing keyword token types.
    switch(l->buf[0]) {
        case 'i':
            if(l->buf[1] == 'n') {
                if(!strcmp(l->buf, "int")) {
                    ty = T_INT;
                }
            }
            break;

        case 'r':
            if(l->buf[1] == 'e') {
                // TODO: Replace all these strcmps with comparisons
                // to interned strings.
                if(!strcmp(l->buf, "return")) {
                    ty = T_RETURN;
                }
            }
            break;

        case 'v':
            if(l->buf[1] == 'o') {
                if(!strcmp(l->buf, "void")) {
                    ty = T_VOID;
                }
            }
            break;
    }

    return token(l, ty);
}

struct token
lex(struct lexer *l) {
    while(is_whitespace(l->peek)) { advance(l); }

    begin(l);

    int first = advance(l);

    if(is_num(first)) {
        return number(l);
    }

    if(is_alpha(first)) {
        return identifier(l);
    }

    switch(first) {
        case EOF: return token(l, T_EOF);
        case '(': return token(l, T_LPAREN);
        case ')': return token(l, T_RPAREN);
        case '{': return token(l, T_LBRACE);
        case '}': return token(l, T_RBRACE);
        case ';': return token(l, T_SEMICOLON);
        default:
            error("Invalid token: Unexpected character '%c'.", first);
    }
}




