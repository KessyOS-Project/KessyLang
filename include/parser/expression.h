#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <stddef.h>
#include <parser/ast.h>
#include <lexer.h>

AST_OP arithop(LEX_TOKEN token);
struct ASTNode* binexpr(size_t start_line);

#endif
