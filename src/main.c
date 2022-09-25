#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <panic.h>
#include <lexer.h>
#include <parser/parser.h>
#include <parser/ast.h>

static const char* current_file = NULL;


__attribute__((noreturn)) void panic(void) {
    printf("[Error happened in %s]\n", current_file);
    ast_nodebuf_destroy();
    exit(1);
}


static void compile(const char* file) {
    current_file = file;

    FILE* fp = fopen(file, "r");

   /*
    *   Do some error checking and panic
    *   if something goes wrong.
    *
    */

    if (!(fp)) {
        printf(PANIC_START "Error: Could not open file!\n");
        perror(file); 
        panic();
    }
    
    // Get size of file.
    fseek(fp, 0, SEEK_END);
    size_t fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    /*
     *  Allocate a buffer to hold our file contents
     *  so we can parse it.
     */

    char* buf = calloc(fsize + 1, sizeof(char));
    fread(buf, sizeof(char), fsize, fp);
    lexer_init(buf);
    parse();

    ast_nodebuf_destroy();
    free(buf);
    fclose(fp);
}


int main(int argc, char** argv) {
	for (int i = 1; i < argc; ++i) {
        compile(argv[i]);
	}

	return 0;
}
