#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Flashcard
{
    char word[100];
    char definition[100];

};

int AddSet() //create new set file (title.txt) and add title to set_list
{
    char file_name[50];
    char title[50];

    printf("Enter title (or type 'cancel' to go back): ");
    gets(title);

    sprintf(file_name,"%s.txt",title);

    FILE *fp = fopen(file_name,"w");
    FILE *master = fopen("set_list.txt","w");
    if(fp == NULL||master == NULL)
    {
        printf("<<Error open file>>");
        return 101;
    }

    fprintf(master,"%s\n",title);

    fclose(fp);
    fclose(master);
}

int AddCard(char *title)
{
    char w[100];
    char d[100];
    char file_name[50];

    sprintf(file_name,"%s.txt",title);
    printf("Enter word (or enter 0 to go back): ");
    gets(w);

    printf("Enter definition (or enter 0 to go back): ");
    gets(d);

    FILE *fp = fopen(file_name,"w");
    if(fp == NULL)
    {
        printf("<<Error open file>>");
        return 101;
    }

    fprintf(fp,"%s:%s\n",w,d);

    fclose(fp);
}

int CardInSet(char *title)
{
    char file_name[50];
    char str[200];
    sprintf(file_name,"%s.txt",title);

    FILE *fp = fopen(file_name,"r");
    if(fp == NULL)
    {
        printf("<<Error open file>>");
        return 101;
    }

    while(fgets(str,100,fp)!= NULL)
    {
        printf("%s\n",str);
    }
    fclose(fp);
}
int SetList() //print all list
{
    char str[200];
    FILE *fp = fopen("set_list.txt","r");
    if(fp == NULL)
    {
        printf("<<Error open file>>");
        return 101;
    }
    while(fgets(str,100,fp)!= NULL)
    {
        printf("%s\n",str);
    }
    fclose(fp);
}
int main()
{
    char title[] = "Alphabet";
    AddSet();
    SetList();
    AddCard(title);
    CardInSet(title);

    return 0;
}
