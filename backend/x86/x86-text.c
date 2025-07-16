#include "backend/x86/x86.h"

#include <inttypes.h>

struct op_info {
    const char *name;
    uint32_t args;
};

static struct op_info optable[] = {
    [O_MOV] = { "mov", 2 },
    [O_RET] = { "ret", 0 },
};

static void
operand(FILE *out, struct x86_operand *op) {
    switch(op->kind) {
        case K_REG: {
            fprintf(out, "%%eax");
        }
        break;

        case K_IMM: {
            fprintf(out, "$%" PRIu64, op->imm);
        }
        break;
    }
}

static void
insn(FILE *out, struct x86_insn *insn) {
    struct op_info info = optable[insn->op];

    fprintf(out, "\t%s ", info.name);
    if(info.args > 0) {
        operand(out, &insn->src);
        if(info.args > 1) {
            fprintf(out, ", ");
            operand(out, &insn->dest);
        }
    }
    fprintf(out, "\n");
}

static void
function(FILE *out, struct x86_function *function) {
    fprintf(out, "\t.global %s\n", function->name.in);
    fprintf(out, "%s:\n", function->name.in);
    list_foreach(&function->insns, i) {
        insn(out, &function->insns.at[i]);
    }
}

void
emit_text_x86(FILE *out, struct x86_program *program) {
    list_foreach(&program->functions, i) {
        function(out, &program->functions.at[i]);
    }

    fprintf(out, "\t.section .note.GNU-stack,\"\",@progbits\n");
}