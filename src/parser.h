#ifndef BENCC_PARSER_H
#define BENCC_PARSER_H

#include "ast.h"
#include "lex.h"

struct parser {
    struct lexer lex;
    struct token peek;
};

void parse_init(struct parser*, FILE*);
void parse_destroy(struct parser*);

struct program* parse(struct parser*);

#endif