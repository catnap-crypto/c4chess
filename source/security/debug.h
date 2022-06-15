#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

#include "../pp4m/pp4m.h"

extern PP4M_HOOK *glo_debug_list;

int DEBUG_PrintBox(const char *format, ...);
int DEBUG_InitBox(void);
int DEBUG_QuitBox(void);

#endif
