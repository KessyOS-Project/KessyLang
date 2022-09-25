#include <parser/ast.h>
#include <panic.h>
#include <stdlib.h>
#include <stddef.h>

static struct ASTNode** allocd_nodes = NULL;
size_t n_allocd_nodes = 0;


void ast_nodebuf_destroy(void) {
    for (size_t i = 0; i < n_allocd_nodes; ++i) {
        free(allocd_nodes[i]);
    }

    free(allocd_nodes);
    allocd_nodes = NULL;
}


/*
 *  When a node is allocated, it will be
 *  pushed to this buffer so when the compiler
 *  is done these nodes are freed.
 *
 */

static void push_allocd_node(struct ASTNode* n) {
    allocd_nodes[n_allocd_nodes++] = n;
    allocd_nodes = realloc(allocd_nodes, sizeof(struct ASTNode*) * (n_allocd_nodes + 1));
}


struct ASTNode* mkastnode(AST_OP op, struct ASTNode* left, struct ASTNode* right, int64_t ival) {
    if (allocd_nodes == NULL) {
        allocd_nodes = malloc(sizeof(struct ASTNode*) + (n_allocd_nodes + 1));
        if (allocd_nodes == NULL) {
            printf(PANIC_START "__INTERNAL_ERROR__: Failed to allocate node buffer in %s()\n", __func__);
            panic();
        }
    }

    struct ASTNode* n = malloc(sizeof(struct ASTNode));

    if (n == NULL) {
        printf(PANIC_START "__INTERNAL_ERROR__: Failed to allocate node in %s()\n", __func__);
        panic();
    }

    n->op = op;
    n->left = left;
    n->right = right;
    n->ival = ival;
    push_allocd_node(n);
    return n;
}


struct ASTNode* mkastleaf(AST_OP op, int64_t ivalue) {
    return mkastnode(op, NULL, NULL, ivalue);
}

struct ASTNode* mkastunary(AST_OP op, struct ASTNode* left, struct ASTNode* right, int64_t ivalue) {
    return mkastnode(op, left, NULL, ivalue);
}
