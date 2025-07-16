#ifndef BENCC_AST_H
#define BENCC_AST_H

#include <stdint.h>

#include "list.h"

struct stmt;
struct expr;
struct function;
struct program;

enum expr_type {
    E_CONSTANT
};

enum stmt_type {
    S_RET
};

struct expr {
    union {
        struct {
            uint64_t value;
        } constant;
    };
    enum expr_type type;
};

struct stmt {
    union {
        struct {
            struct expr *value;
        } ret;
    };
    enum stmt_type type;
};

struct function {
    list_of(struct stmt*) stmts;
};

struct program {
    list_of(struct function*) functions;
};

#endif