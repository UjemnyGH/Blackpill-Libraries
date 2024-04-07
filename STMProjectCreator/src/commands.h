#ifndef __CREATOR_COMMANDS_
#define __CREATOR_COMMANDS_

#include <malloc.h>
#include <string.h>
#include <stdint.h>

typedef void (*PFN_CmdFunc)(char* cmd);

typedef struct cmd_s {
    PFN_CmdFunc mCmdFn;
    char mCmd[0x100];
} cmd_t;

typedef struct command_handler_s {
    cmd_t **mCmds;
    size_t mCmdSize;
} cmd_handler_t;

#endif