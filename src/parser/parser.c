#include <stdint.h>
#include <stdio.h>
#include <parser/parser.h>
#include <parser/expression.h>

struct Token last_token;


int64_t interp_tree(struct ASTNode* root) {
    int64_t leftval, rightval;

    if (root->left) {
        leftval = interp_tree(root->left);
    }

    if (root->right) {
        rightval = interp_tree(root->right);
    }

    switch (root->op) {
        case A_ADD:
            return leftval + rightval;
        case A_SUB:
            return rightval - leftval;
        case A_MUL:
            return rightval * leftval;
        case A_DIV:
            return leftval / rightval;
        case A_INTLIT:
            return root->ival;
    }
}


void parse(void) {
    struct ASTNode* n;
    uint8_t run = scan(&last_token);

    while (run) {
        n = binexpr(last_token.line_number);
        printf("%d\n", interp_tree(n));
        run = scan(&last_token);
    }
}

