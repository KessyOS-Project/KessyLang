#include <lexer.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <panic.h>

#define NEXT_TOKEN(n) buf_idx += n; c = lbuf[buf_idx]
#define ISDIGIT_ASCII(c) c >= '0' && c <= '9'

static const char* lbuf = NULL;
static size_t buf_idx = 0;
static size_t line_number = 1;
static char c;


static uint8_t should_ignore(char c) {
    switch (c) {
        case '\f':
        case '\r':
        case '\n':
            ++line_number;
        case ' ':
            return 1;
    }

    return 0;
}


void lexer_init(const char* buf) {
    lbuf = buf;
}


static long long scanint(void) {
    struct TokInt v;
    size_t vidx = 0;

    while (ISDIGIT_ASCII(c)) {
        v.ll[vidx++] = c;
        NEXT_TOKEN(1);
    }
    
    switch (c) {
        case ';':
        case '+':
        case '-':
        case '*':
        case '/':
            break;
        default:
            if (should_ignore) {
                break;
            }

            printf(PANIC_START "Syntax error: Unknown token found while scanning - line %d\n", line_number);
            panic();
    }

    --buf_idx;
    return atoll(v.ll);
}


uint8_t scan(struct Token* out) {
    c = lbuf[buf_idx];
    while (should_ignore(c)) {
        NEXT_TOKEN(1);
    }

    switch (c) {
        case 0:
            return 0;
        case '+':
            out->type = TT_PLUS;
            break;
        case '-':
            out->type = TT_MINUS;
            break;
        case '*':
            out->type = TT_STAR;
            break;
        case '/':
            out->type = TT_SLASH;
            break;
        default:
            if (ISDIGIT_ASCII(c)) {
                out->v.val_int = scanint();
                printf("%d\n", out->v.val_int);
            } else {
                printf(PANIC_START "Syntax error: Invalid token found while scanning - line %d\n", line_number);
                panic();
            }

            break;
    }

    NEXT_TOKEN(1);
    return 1;
}
