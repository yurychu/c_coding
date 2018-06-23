#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <string.h>

    #define BUFF_SIZE 2048
    static char buffer[BUFF_SIZE];

    // fake readline func
    char * readline(char* prompt)
    {
        fputs(prompt, stdout);
        fgets(buffer, BUFF_SIZE, stdin);
        char * cpy = malloc(strlen(buffer) + 1);
        strcpy(cpy, buffer);
        cpy[strlen(cpy) - 1] = '\0';
        return cpy;
    }

    // fake add_history
    void add_history(char * unused)
    {

    }
#else
    #include <editline/readline.h>
    #include <editline/history.h>
#endif

#include "mpc.h"


int main(int argc, char ** argv)
{
    // Create parsers
    mpc_parser_t * Number = mpc_new("number");
    mpc_parser_t * Operator = mpc_new("operator");
    mpc_parser_t * Expr = mpc_new("expr");
    mpc_parser_t * Lispy = mpc_new("lispy");
    
    mpca_lang(MPCA_LANG_DEFAULT,
        "                                                           \
            number  : /-?[0-9]+/ ;                                  \
            operator: '+' | '-' | '*' | '/' ;                       \
            expr    : <number> | '(' <operator> <expr>+ ')' ;       \
            lispy   : /^/ <oeperator> <expr>+ /$/ ;                  \
        ",
        Number, Operator, Expr, Lispy);
            


    puts("Lispy Version 1");
    puts("Ctrl+C to Exit\n");
    
    while (1){
        char * input = readline("lispy> ");
        if (*input == 'q')
            break;
        
        add_history(input);
        
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r)){
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        }
        else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }
        
        free(input);
    }
    
    mpc_cleanup(4, Number, Operator, Expr, Lispy);

    return 0;
}

// mpc files needed
// cc -std=c99 -Wall parsing.c mpc.c -ledit -lm -o parsing.out
