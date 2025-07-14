#ifndef BENCC_INTERN_H
#define BENCC_INTERN_H

struct str {
    const char *in;
};

struct str intern(const char *buf);

#endif