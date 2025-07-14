#include "intern.h"

struct str
intern(const char *buffer) {
    // We don't need actual string interning yet... Well, sorta...
    return (struct str){ .in = buffer };
}