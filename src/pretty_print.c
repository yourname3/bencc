#include "pretty_print.h"

#include <stdio.h>
#include <stdarg.h>
#include <inttypes.h>

#include "ast.h"

struct pp {
    int indent;
};

static void
pp_printf(struct pp *pp, const char *fmt, ...) {
    for(int i = 0; i < pp->indent; ++i) {
        fputc(' ', stdout);
    }
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

static void
pp_begin(struct pp *pp, const char *item) {
    pp_printf(pp, "%s {\n", item);
    pp->indent += 4;
}

static void
pp_end(struct pp *pp) {
    pp->indent -= 4;
    pp_printf(pp, "}\n");
}

static void
pp_expr(struct pp *pp, struct expr *expr) {
    switch(expr->type) {
        case E_CONSTANT: {
            printf("constant(%" PRIu64 ")", expr->constant.value);
        }
        break;
    }
}

static void
pp_stmt(struct pp *pp, struct stmt *stmt) {
    switch(stmt->type) {
        case S_RET: {
            pp_begin(pp, "return ");
            pp_expr(pp, stmt->ret.value);
            pp_end(pp);
        }
        break;
    }
}

static void
pp_function(struct pp *pp, struct function *func) {
    pp_begin(pp, "function");
    list_foreach(&func->stmts, i) {
        pp_stmt(pp, func->stmts.at[i]);
    }
    pp_end(pp);
}

void
pretty_print(struct program *prog) {
    struct pp pp = {0};

    pp_begin(&pp, "program");
    list_foreach(&prog->functions, i) {
        pp_function(&pp, prog->functions.at[i]);
    }
    pp_end(&pp);
}