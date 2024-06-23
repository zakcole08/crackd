#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

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
#define PROGRAM_LOCATION "/etc/crackd"

int c;
int nl1 = 0, wc1 = 0, cc1 = 0;
int nl2 = 0, wc2 = 0, cc2 = 0;
int nl = 0, wc = 0, cc = 0;
int state = OUT;
char command[256];
char editor[254];
char line[256];
FILE *in_file;
FILE *config_file;

void config()
{
    if (access(PROGRAM_LOCATION"/crackd.cnf", F_OK) != 0)
    {
        config_file = fopen(PROGRAM_LOCATION"/crackd.cnf", "w");
        fprintf(config_file, "TEXT_EDITOR=vim\n");
        fclose(config_file);
    }
    
    config_file = fopen(PROGRAM_LOCATION"/crackd.cnf", "r");
    if (config_file == NULL)
    {
        fprintf(stderr, "Could not open config file\n");
        exit(1);
    }

    while (fgets(line, sizeof(line), config_file) != NULL)
    {
        if (strncmp(line, "TEXT_EDITOR=", 12) == 0)
        {
            strncpy(editor, line + 12, sizeof(editor) - 1);
            editor[strcspn(editor, "\n")] = '\0';
            fclose(config_file);
            return;
        }
    }
    
    fclose(config_file);
    
    printf("Enter name of your preferred text editor: ");
    scanf("%255s", editor);
     
    config_file = fopen(PROGRAM_LOCATION"/crackd.cnf", "w");
    if (config_file == NULL)
    {
        fprintf(stderr, "Could not open config file for writing\n");
        exit(1);
    }
    fprintf(config_file, "TEXT_EDITOR=%s", editor);
    fclose(config_file);
}

int get_stats(char **argv, int *nl, int *wc, int *cc)
{
    in_file = fopen(argv[1], "r");
    
    if (in_file == NULL)
    {
        return 2;
    }

    while ((c = fgetc(in_file)) != EOF)
    {
        ++(*cc);

        if (c == '\n')
        {
            ++(*nl);
        }

        if (c == '\n' || c == '\t' || c == ' ')
        {
            state = OUT;
        }
        else if (state == OUT)
        {
            state = IN;
            ++(*wc);
        }
    }
    
    fclose(in_file);
}

void print_grid(char **argv, int nl, int wc, int cc) {

    printf(BOLD "\n-> CRACKD %s\n\n", argv[1]);
    printf(BOLD WHITE "%-15s %-15s %-15s\n" RESET, "Lines", "Words", "Characters");
    printf(BOLD WHITE "%-15s %-15s %-15s\n" RESET, "-----", "-----", "----------");
    printf(BOLD GREEN "%-15d" RESET BOLD YELLOW " %-15d" RESET BOLD CYAN " %-15d\n\n" RESET, nl, wc, cc);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    config();

    get_stats(argv, &nl1, &wc1, &cc1);

    snprintf(command, sizeof(command), "%s %s", editor, argv[1]);
    int result = system(command);
    if (result != 0)
    {
        return -1;
    }

    get_stats(argv, &nl2, &wc2, &cc2);
    nl = nl2 - nl1;
    wc = wc2 - wc1;
    cc = cc2 - cc1;
    print_grid(argv, nl, wc, cc);

    return 0;
}