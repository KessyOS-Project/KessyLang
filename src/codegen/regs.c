#include <codegen/regs.h>
#include <codegen/compile.h>
#include <stdint.h>
#include <stdio.h>


static const char* rregs[4] = {"r8", "r9", "r10", "r11"};
static uint8_t regbmp = 0xFF;


static REG_T alloc_reg(void) {
    for (int i = 0; i < sizeof(regbmp)*8; ++i) {
        if (regbmp & (1 << i)) {
            regbmp &= ~(1 << i);
            return i;
        }
    }

    return -1;
}


static void free_reg(REG_T r) {
    if (r > (sizeof(regbmp)*8) - 1 || r < 0) {
        return;
    }

    regbmp |= (1 << r);
}


REG_T reg_load(int64_t value) {
    REG_T r = alloc_reg();
    fprintf(g_outfile, "\tmov %s, %d\n", rregs[r], value);
    return r;
}


REG_T reg_add(REG_T r1, REG_T r2) {
    fprintf(g_outfile, "\tadd %s, %s\n", rregs[r1], rregs[r2]);
    free_reg(r2);
    return r1;
}


REG_T reg_sub(REG_T r1, REG_T r2) {
    fprintf(g_outfile, "\tsub %s, %s\n", rregs[r1], rregs[r2]);
    free_reg(r2);
    return r1;
}

REG_T reg_mul(REG_T r1, REG_T r2) {
    fprintf(g_outfile, "\timul %s, %s\n", rregs[r1], rregs[r2]);
    free_reg(r2);
    return r1;
}

REG_T reg_div(REG_T r1, REG_T r2) {
    fprintf(g_outfile, "\tmov rax, %s\n", rregs[r1]);
    fprintf(g_outfile, "\tcqo\n");
    fprintf(g_outfile, "\tidiv %s\n", rregs[r2]);
    fprintf(g_outfile, "\tmov %s, rax\n", rregs[r1]);
    free_reg(r2);
    return r1;
}

void reg_printint(REG_T r) {
    fprintf(g_outfile, "\tmov rdi, %s\n", rregs[r]);
    fprintf(g_outfile, "\tcall printint\n");
    free_reg(r);
}
