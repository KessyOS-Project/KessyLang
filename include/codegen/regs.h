#ifndef REGS_H
#define REGS_H

#include <stdint.h>


typedef int8_t REG_T;
typedef int64_t QWORD_T;

REG_T reg_load(int64_t value);
REG_T reg_add(REG_T r1, REG_T r2);
REG_T reg_mul(REG_T r1, REG_T r2);
REG_T reg_sub(REG_T r1, REG_T r2);
REG_T reg_div(REG_T r1, REG_T r2);
void reg_printint(REG_T r);

#endif
