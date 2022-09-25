#include <parser/expression.h>
#include <parser/ast.h>
#include <parser/parser.h>
#include <lexer.h>
#include <panic.h>

static struct ASTNode* primary(void) {
    struct ASTNode* n;

    switch (last_token.type) {
        case TT_INTLIT:
            n = mkastleaf(A_INTLIT, last_token.v.val_int);
            scan(&last_token);
            return n;
        default:
            printf(PANIC_START "Syntax error - line %d\n", last_token.line_number);
#ifdef KESSL_DEBUG_MODE
            printf("[debug-mode]: Token encountered: %d\n", last_token.type);
#endif
            panic();
    }
}


struct ASTNode* binexpr(size_t start_line) {
    struct ASTNode* n;
    struct ASTNode* left;
    struct ASTNode* right;
    AST_OP nodetype;
    
    left = primary();

    if (last_token.type == TT_EOF) {
        return left;
    }

    nodetype = arithop(last_token.type);
    scan(&last_token);

    right = binexpr(last_token.line_number);
    n = mkastnode(nodetype, left, right, 0);
    return n;
}


AST_OP arithop(LEX_TOKEN token) {
    if (token < TT_PLUS || token > TT_INTLIT) {
        printf(PANIC_START "__INTERNAL_ERROR__: Invalid token found in %s()\n", __func__);
        panic();
    }

    return (AST_OP)token;
}
