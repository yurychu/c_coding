#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <editline/history.h>


int main(int argc, char ** argv)
{
    puts("Lispy Version 1");
    puts("Ctrl+C to Exit\n");
    
    while (1){
        char * input = readline("lispy> ");
        
        add_history(input);
        
        printf("You're a %s\n", input);
        
        free(input);
    }

    return 0;
}

// sudo apt-get install libedit-dev
// cc -std=c99 -Wall prompt.c -ledit -o prompt.out
