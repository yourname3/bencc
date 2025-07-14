#ifndef BENCC_ERROR_H
#define BENCC_ERROR_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

static inline _Noreturn void
error(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    // TODO: Longjmp to error recovery point.
    exit(1);
}

#endif