#ifndef COMPILE_H
#define COMPILE_H

#include <stdio.h>
#include <parser/ast.h>

/*
 *  Compile start: Sets up program.
 *  Compile end:   Ends program.
 *
 *
 */
void compile_start(void);
void compile_end(void);
int64_t ast_gen(struct ASTNode* n);
extern FILE* g_outfile;

#endif
