#ifndef PANIC_H
#define PANIC_H

#include <stddef.h>

#define PANIC_START "\033[0;31m"


__attribute__((noreturn)) void panic(void);


/*
 *  Used for telling which file an
 *  error happened in.
 */

void set_current_path(const char* path);

#endif
