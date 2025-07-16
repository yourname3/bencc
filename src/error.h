#ifndef BENCC_ERROR_H
#define BENCC_ERROR_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

static inline void
error_begin(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

static inline void
v_error_begin(const char *fmt, va_list args) {
    vprintf(fmt, args);
}


static inline _Noreturn void
error(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    putc('\n', stdout);

    // TODO: Longjmp to error recovery point.
    exit(1);
}

static inline _Noreturn void
v_error(const char *fmt, va_list args) {
    vprintf(fmt, args);
    putc('\n', stdout);

    // TODO: Longjmp to error recovery point.
    exit(1);
}

#endif