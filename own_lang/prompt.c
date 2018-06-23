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
    
#endif  // _WIN32


int main(int argc, char ** argv)
{
    puts("Lispy Version 1");
    puts("Ctrl+C to Exit\n");
    
    while (1){
        char * input = readline("lispy> ");
        
        add_history(input);
        
        printf("You're a: %s\n", input);
        
        free(input);
    }

    return 0;
}

// sudo apt-get install libedit-dev
// cc -std=c99 -Wall prompt.c -ledit -o prompt.out
