#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define IN 1
#define OUT 0

int c;
int nl = 1;
int wc = 0, cc = 0;
int state = OUT;
char command[256];
FILE *inFile;

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

        printf("%c", c);
    }
        
        printf("\nLines: %d\n", nl);
        printf("Words: %d\n", wc);
        printf("Characters: %d\n", cc);

    return 0;
}