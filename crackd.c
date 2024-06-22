#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"
#define BOLD    "\x1b[1m"

#define IN 1
#define OUT 0

int c;
int nl = 1;
int wc = 0, cc = 0;
int state = OUT;
char command[256];
FILE *inFile;

void print_grid(char **argv, int nl, int wc, int cc) {

    printf(BOLD "\n-> CRACKD %s\n\n", argv[1]);
    printf(BOLD WHITE "%-15s %-15s %-15s\n" RESET, "Lines", "Words", "Characters");
    printf(BOLD WHITE "%-15s %-15s %-15s\n" RESET, "-----", "-----", "----------");
    printf(BOLD GREEN "%-15d" RESET BOLD YELLOW " %-15d" RESET BOLD CYAN " %-15d\n\n" RESET, nl, wc, cc);
}

int main(int argc, char **argv)
{
    snprintf(command, sizeof(command), "vim %s", argv[1]);
    int result = system(command);
    if (result != 0)
    {
        return -1;
    }

    inFile = fopen(argv[1], "r");
    
    if (inFile == NULL)
    {
        fprintf(stderr, "Cannot open file for reading: %s\n", argv[1]);
        return 2;
    }

    while ((c = fgetc(inFile)) != EOF)
    {
        ++cc;

        if (c == '\n')
        {
            ++nl;
        }

        if (c == '\n' || c == '\t' || c == ' ')
        {
            state = OUT;
        }
        else if (state == OUT)
        {
            state = IN;
            ++wc;
        }
    }
    
    fclose(inFile);
  
    print_grid(argv, nl, wc, cc);

    return 0;
}
