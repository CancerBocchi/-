#ifndef __DEBUG_TOOL_H__
#define __DEBUG_TOOL_H__

#include "rtthread.h"
#include "finsh.h"
#include "shell.h"

extern float a;

#define DEBUG_FLOAT 0
#define DEBUG_INT 1

#define DEBUG_VARNUM 2

#define SETARG_HELP "you can use like this:\n\
                    setarg show             ----- show the arg in the register \n\
                    setarg <target> <value> ----- change the value of the target\n"


typedef struct argu_change
{
    char* name;
    uint8_t conp;
    void* arg;

}arg_change;

extern arg_change arg_register[];

void debug_tool_init();

#endif