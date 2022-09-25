#include <parser.h>

struct Token last_token;


void parse(void) {
    uint8_t run = scan(&last_token);

    while (run) {
        run = scan(&last_token);
    }
}

