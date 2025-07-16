#ifndef BENCC_X86_H
#define BENCC_X86_H

#include <stdint.h>
#include <stdio.h>

#include "src/list.h"
#include "src/intern.h"

struct x86_program;
struct x86_function;
struct x86_insn;
struct x86_operand;

enum x86_opcode {
    O_MOV,
    O_RET
};

enum x86_register {
    R_EAX
};

enum x86_kind {
    K_REG,
    K_IMM
};

struct x86_operand {
    union {
        enum x86_register reg;
        uint64_t          imm;
    };
    enum x86_kind kind;
};

struct x86_insn {
    enum x86_opcode op;
    struct x86_operand src;
    struct x86_operand dest;
};

struct x86_function {
    struct str name;
    list_of(struct x86_insn) insns;
};

struct x86_program {
    list_of(struct x86_function) functions;
};

struct program;

void emit_text_x86(FILE *out, struct x86_program *program);
struct x86_program* compile_to_x86(struct program *program);

#endif