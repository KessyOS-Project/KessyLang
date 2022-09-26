#include <codegen/compile.h>
#include <codegen/regs.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define OBJ_FILENAME_LEN 6

FILE* g_outfile = NULL;


/*
 *  Generates filename for object file.
 *  Only can use one string at a time!
 */

const char* obj_filename_gen(void) {
    srand(time(NULL));

    const char CHARSET[] = "abcdefghijklnmopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    static char fname[OBJ_FILENAME_LEN + 4];
    
    int i;
    for (i = 0; i < OBJ_FILENAME_LEN; ++i) {
        fname[i] = CHARSET[rand() % sizeof(CHARSET)];
    }

    // Add .o and null terminate.
    fname[i++] = '.';
    fname[i++] = 'o';
    fname[i] = '\0';
    return fname;
}

static void prologue(void) {
  fputs(
          "extern printf\n\n"
          "section .data\n"
          "integer: db \"%d\", 0xA, 0\n"
          "string: db \"%s\", 0xA, 0\n\n"
          "section .text\n" 
          "printint:\n"
          "\tmov rsi, rdi\n"
          "\tmov rdi, integer\n"
          "\tpush rsp\n"
          "\tcall [rel printf wrt ..got]\n"
          "\tpop rsp\n"
          "\tret\n\n"
          "printstr:\n"
          "\tmov rsi, rdi\n"
          "\tmov rdi, string\n"
          "\tpush rsp\n"
          "\tcall [rel printf wrt ..got]\n"
          "\tpop rsp\n"
          "\tret\n"
          "\n"
          "main:\n"
          "\tpush rbp\n"
          "\tmov rsp, rbp\n",
  g_outfile);
}


void epilouge(void) {
    fputs(
        "\tmov rax, 0\n"
        "\tleave\n"
        "\tret\n", g_outfile);
}


void compile_start(void) {
    g_outfile = fopen("kessy-out.asm", "w");

    prologue();
}

void compile_end(void) {
    epilouge();

    if (g_outfile != NULL)
        fclose(g_outfile);

    g_outfile = NULL;
}

int64_t ast_gen(struct ASTNode* n) {
    int leftreg, rightreg;

    if (n->left) {
        leftreg = ast_gen(n->left);
    }

    if (n->right) {
        rightreg = ast_gen(n->right);
    }

    switch (n->op) {
        case A_ADD:
            return reg_add(leftreg, rightreg);
        case A_SUB:
            return reg_sub(leftreg, rightreg);
        case A_MUL:
            return reg_mul(leftreg, rightreg);
        case A_DIV:
            return reg_div(leftreg, rightreg);
        case A_INTLIT:
            return reg_load(n->ival);
    }
}
