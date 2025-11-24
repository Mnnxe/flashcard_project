#include <stdio.h>
#include <windows.h>

void readtext(char *story)
{
    char file_name[50];
    char ch;

    sprintf(file_name,"%s.txt",story);

    FILE *fp;
    fp = fopen(file_name,"r");
    if(fp == NULL)
    {
        printf("Can't Open File\n");
        return;
    }

    printf("----------------------------------------------------------------------------------------------------------------------\n");

    while(1)
    {   fscanf(fp,"%c",&ch);
        if(ch == NULL) break;
        else
        {

            if(ch == '_') printf(" ");
            else if(ch == '*') printf("\n");
            else if(ch == '>') printf("\t");
            else if(ch == '&') printf("\033[0m");
            else if(ch == '#') printf("\033[91m");
            else if(ch == '=') printf("\033[94m");
            else if(ch == '%') printf("\033[1;92m");
            else if(ch == '|') printf("\033[4m");
            else if(ch == '+') printf("\033[1m");
            else if(ch == '^') Sleep(400);
            else if(ch == '/') break;
            else
            {
                printf("%c",ch);
                Sleep(20);
            }
        }

    }
    printf("\n----------------------------------------------------------------------------------------------------------------------\n");
}
int main()
{
    readtext("defeat_story");
    readtext("intro_story");
    readtext("win_story");
}
