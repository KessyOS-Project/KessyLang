#include <stdint.h>
#include <stdio.h>
#include <parser/parser.h>
#include <parser/expression.h>
#include <codegen/compile.h>

struct Token last_token;


void parse(void) {
    struct ASTNode* n;
    uint8_t run = scan(&last_token);
    compile_start();

    while (run) {
        n = binexpr(last_token.line_number);
        ast_gen(n);
        run = scan(&last_token);
    }

    compile_end();
}

