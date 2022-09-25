#ifndef AST_H
#define AST_H

#include <stdint.h>


typedef enum {
    A_ADD,
    A_SUB,
    A_MUL,
    A_DIV,
    A_INTLIT
} AST_OP;


struct ASTNode {
    AST_OP op;
    struct ASTNode* left;
    struct ASTNode* right;
    int64_t ival;               // Integer value.
};


struct ASTNode* mkastnode(AST_OP op, struct ASTNode* left, struct ASTNode* right, int64_t ival);
struct ASTNode* mkastleaf(AST_OP op, int64_t ivalue);
struct ASTNode* mkastunary(AST_OP op, struct ASTNode* left, struct ASTNode* right, int64_t ivalue);
void ast_nodebuf_destroy(void);

#endif
