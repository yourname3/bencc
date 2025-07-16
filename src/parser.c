#include "parser.h"
#include "ast.h"

#include <stdbool.h>

#include "alloc.h"
#include "error.h"

#define my(Ty, name) Ty name = calloc(1, sizeof(*name))

static struct token
advance(struct parser *p) {
    struct token cur = p->peek;
    p->peek = lex(&p->lex);
    return cur;
}

static bool
at(struct parser *p, enum token_type ty) {
    return p->peek.type == ty;
}

static bool
eat(struct parser *p, enum token_type ty) {
    if(p->peek.type == ty) {
        advance(p);
        return true;
    }
    return false;
}

static _Noreturn void
expected(struct parser *p, const char *fmt, ...) {
    error_begin("expected ");

    va_list args;
    va_start(args, fmt);
    v_error_begin(fmt, args);
    va_end(args);

    error(", got '%s'", p->peek.str.in);
}

static struct token
expect(struct parser *p, enum token_type ty, const char *fmt, ...) {
    struct token tok = p->peek;
    if(!eat(p, ty)) {
        error_begin("expected ");

        va_list args;
        va_start(args, fmt);
        v_error_begin(fmt, args);
        va_end(args);

        error(", got '%s'", p->peek.str.in);
    }
    return tok;
}

void
parse_init(struct parser* p, FILE* f) {
    lex_init(&p->lex, f);
    p->peek = (struct token){
        .str = intern("error"),
        .type = T_ERROR
    };
    // Prime the parser with the first token.
    advance(p);
}

void
parse_destroy(struct parser* p) {
    lex_destroy(&p->lex);
}

static struct expr*
expr(struct parser *p) {
    my(struct expr*, e);

    switch(p->peek.type) {
        case T_NUM: {
            e->constant.value = atoi(p->peek.str.in);
            e->type = E_CONSTANT;
            advance(p);
        }
        break;

        default: {
            expected(p, "expression");
        }
    }

    return e;
}

static struct stmt*
stmt(struct parser *p) {
    // TODO: How to free these when we encounter errors?
    my(struct stmt*, s);

    switch(p->peek.type) {
        case T_RETURN: {
            advance(p);
            s->ret.value = expr(p);
            s->type = S_RET;
        }
        break;

        default: {
            expected(p, "statement");
        }
    }

    expect(p, T_SEMICOLON, "';' after statement");

    return s;
}

static struct function*
function(struct parser *p, struct token name) {
    my(struct function*, func);

    expect(p, T_LPAREN, "'(' after function name");
    expect(p, T_VOID, "parameter list");
    expect(p, T_RPAREN, "')' after parameter list");
    expect(p, T_LBRACE, "'{' after parameter list");
    while(!at(p, T_RBRACE) && !at(p, T_EOF)) {
        list_push(&func->stmts, stmt(p));
    }
    expect(p, T_RBRACE, "'}' after function body");

    return func;
}

static void
top_level(struct parser *p, struct program *prog) {
    expect(p, T_INT, "type at top-level");
    struct token ident = expect(p, T_ID, "identifier after type name");

    if(at(p, T_LPAREN)) {
        list_push(&prog->functions, function(p, ident));
    }
    else {
        error("unknown top-level declaration");
    }
}

struct program*
parse(struct parser *p) {
    my(struct program*, program);

    while(p->peek.type != T_EOF) {
        top_level(p, program);
    }

    return program;
}


