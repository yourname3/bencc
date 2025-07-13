#ifndef BENCC_OPTIONS_H
#define BENCC_OPTIONS_H

enum opt_stage {
    STAGE_ALL,
    STAGE_LEX,
    STAGE_PARSE,
    STAGE_CODEGEN,
};

struct options {
    enum opt_stage stage;
};

/** The global options variable. */
struct options options = {
    .stage = STAGE_ALL
};

#endif