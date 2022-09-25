#ifndef LEXER_H
#define LEXER_H

#include <stdint.h>
#include <stddef.h>


typedef enum {
	TT_PLUS,
	TT_MINUS,
	TT_STAR,
	TT_SLASH,
	TT_INTLIT,
    TT_EOF,
} LEX_TOKEN;


struct TokInt {
    char ll[25];            // Long long.
};

struct Token {
	LEX_TOKEN type;

	union {
		int64_t val_int;
		const char* tokstr;
	} v;

    size_t line_number;
};


/*
 * Scans for a token.
 *
 * @param out: Token output.
 * @returns:   1 if there are more tokens
 *             otherwise 0.
 *
 *
 */

uint8_t scan(struct Token* out);

/*
 *  Sets up the lexer.
 */

void lexer_init(const char* buf);


#endif
