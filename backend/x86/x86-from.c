#include "backend/x86/x86.h"

#include "src/ast.h"
#include "src/alloc.h"

static void
mov(struct x86_function *out, struct x86_operand dest, struct x86_operand src) {
    list_push(&out->insns, (struct x86_insn){
        .op = O_MOV,
        .src = src,
        .dest = dest
    });
}

static struct x86_operand
imm(uint64_t val) {
    return (struct x86_operand){ .imm = val, .kind = K_IMM };
}

static struct x86_operand
reg(enum x86_register reg) {
    return (struct x86_operand){ .reg = reg, .kind = K_REG };
}

static void
expr(struct x86_function *out, struct expr *expr, struct x86_operand dest) {
    switch(expr->type) {
        case E_CONSTANT: {
            mov(out, dest, imm(expr->constant.value));
        }
        break;
    }
}

static void
stmt(struct x86_function *out, struct stmt *stmt) {
    switch(stmt->type) {
        case S_RET: {
            expr(out, stmt->ret.value, reg(R_EAX));
            list_push(&out->insns, (struct x86_insn){ .op = O_RET });
        }
        break;
    }
}

static struct x86_function
function(struct function *function) {
    struct x86_function f = {0};
    f.name = function->name;

    list_foreach(&function->stmts, i) {
        stmt(&f, function->stmts.at[i]);
    }

    return f;
}

struct x86_program*
compile_to_x86(struct program *program) {
    struct x86_program *p = zalloc(sizeof(*p));

    list_foreach(&program->functions, i) {
        struct x86_function f = function(program->functions.at[i]);
        list_push(&p->functions, f);
    }

    return p;
}