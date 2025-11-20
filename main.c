#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Flashcard
{
    char word[100];
    char definition[100];
};

//helper function
void clearBuffer()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void trimNewline(char *str)
{
    str[strcspn(str,"\n")] = 0;
}

char GetLine(int line,char *name ,char *buffer)
{
    int current_line = 1;
    char str[100];
    char file_name[100];

    sprintf(file_name,"%s.txt",name);

    FILE *fp = fopen(file_name,"r");
    if(fp == NULL)
    {
        printf("<File is empty>");
        return 0;
    }

    while(fgets(str,sizeof(str),fp) != NULL)
    {
        if(current_line == line)
        {
            trimNewline(str);
            strcpy(buffer,str);

            fclose(fp);
            return 1;
        }
        current_line++;
    }
    fclose(fp);
    return 0;
}

//file management function
void AddSet()
{
    char file_name[50];
    char title[50];

    system("cls");

    printf("Enter title (or enter 0 to go back): ");
    gets(title);

    if(strcmp(title,"0")==0) return;
    else
    {
        sprintf(file_name,"%s.txt",title);

        FILE *fp = fopen(file_name,"w");
        FILE *master = fopen("set_list.txt","a");
        if(fp == NULL||master == NULL)
        {
        printf("<File is empty>");
        return;
        }

        fprintf(master,"%s\n",title);

        fclose(fp);
        fclose(master);
    }

}

void DelSet(char *title)
{
    char str[100];
    char file_name[100];

    sprintf(file_name,"%s.txt",title);

    FILE *fp = fopen("set_list.txt","r");
    FILE *tp = fopen("temp_file.txt","w");
    if(fp == NULL || tp == NULL)
    {
        printf("<File is empty>");
    }

    while(fgets(str,sizeof(str),fp) != NULL )
    {
        trimNewline(str);

        if(strcmp(str,title) != 0)
        {
            fprintf(tp,"%s\n",str);
        }
    }

    fclose(fp);
    fclose(tp);

    remove("set_list.txt");
    remove(file_name);
    rename("temp_card.txt","set_list.txt");



}

int AddCard(char *title)
{
    char w[100];
    char d[100];
    char file_name[50];

    sprintf(file_name,"%s.txt",title);

    FILE *fp = fopen(file_name,"a");
    if(fp == NULL)
    {
        printf("<File is empty>");
        return 1;
    }

    system("cls");

    while(1)
    {
        printf("Enter word (or enter 0 to go back): ");
        gets(w);
        if(strcmp(w,"0")== 0)
            break;
        else
        {
            printf("Enter definition (or enter 0 to go back): ");
            gets(d);
            if(strcmp(d,"0")== 0)
                break;
            else fprintf(fp,"%s:%s\n",w,d);
        }

    }

    fclose(fp);
}

void DelCard(char *word,char *file)
{
    char str[100];

    FILE *fp = fopen(file,"r");
    FILE *tp = fopen("temp_file.txt","w");
    if(fp == NULL || tp == NULL)
    {
        printf("<File is empty>");
    }

    while(fgets(str,sizeof(str),fp) != NULL )
    {
        trimNewline(str);

        if(strcmp(str,word) != 0)
        {
            fprintf(tp,"%s\n",str);
        }
    }

    fclose(fp);
    fclose(tp);

    remove(file);
    rename("temp_file.txt",file);

}

int CardList(char *title)
{
    int line;
    char file_name[50];
    char str[200];
    int count = 1;

    sprintf(file_name,"%s.txt",title);

    FILE *fp = fopen(file_name,"r");
    if(fp == NULL)
    {
        printf("<File is empty>");
        return 0;
    }

    while(fgets(str,sizeof(str),fp)!= NULL)
    {
        printf("%d. %s",count,str);
        count++;
    }
    fclose(fp);
}

int SetList()
{
    char str[200];
    int count = 1;
    FILE *fp = fopen("set_list.txt","r");
    if(fp == NULL)
    {
        printf("<File is empty>");
        return 0;
    }
    while(fgets(str,100,fp)!= NULL)
    {
        printf("%d. %s",count,str);
        count++;
    }
    fclose(fp);
}
void card_menu(char *title)
{
    char choice;
    char file_name[100];
    char card[100];
    int lineNum;

    sprintf(file_name,"%s.txt",title);

    FILE *fp = fopen(file_name,"r");
    if(fp == NULL)
    {
        printf("<File is empty>");
        return;
    }
    fclose(fp);
    do
    {
        system("cls");
        printf("----------%s----------\n",title);
        CardList(title);
        printf("\n");
        printf("A: Add card\n");
        printf("D: Delete card\n");
        printf("X: Back\n");
        choice = getchar();

        if(choice != '\n')
        {
            while(getchar() != '\n');
        }
        choice = tolower(choice);

        switch(choice)
        {
            case 'a':
                AddCard(title);
                system("cls");
                break;
            case 'd':
                printf("Enter line number to delete: ");
                scanf("%d",&lineNum);
                GetLine(lineNum,title,card);
                clearBuffer();
                DelCard(card,file_name);
                break;
            case 'x': return;
            default:

                printf("no choice\n");
        }
    }while (choice != 'x');
}
void set_menu()
{
    char choice;
    char setName[100];
    int lineNum;
    do
    {
        system("cls");
        printf("----------Flashcard Sets----------\n");
        SetList();
        printf("\n");
        printf("A: Add set\n");
        printf("D: Delete set\n");
        printf("M: Manage set\n");
        printf("X: Back\n");
        choice = getchar();

        if(choice != '\n') {
                while(getchar() != '\n');
            }
        choice = tolower(choice);

        switch(choice)
        {
            case 'a':
                AddSet();
                system("cls");
                break;
            case 'd':
                printf("Enter line number: ");
                scanf("%d",&lineNum);
                GetLine(lineNum,"set_list",setName);
                clearBuffer();
                DelSet(setName);
                break;
            case 'm':
                printf("Enter line number: ");
                scanf("%d",&lineNum);
                GetLine(lineNum,"set_list",setName);
                clearBuffer();
                card_menu(setName);
                break;
            case 'x': return;
            default:
                printf("no choice\n");
        }
    }while (choice != 'x');
}
void main_menu()
{
    char choice;

    do
    {
        system("cls");
        printf("1: Start\n");
        printf("2: Manage Sets\n");
        printf("X: Close Program\n");

        choice = getchar();
        choice = tolower(choice);

        switch(choice)
        {
            case '1': printf("Starting game...\n"); break;
            case '2': set_menu(); break;
            case 'x': return;
            default:
                printf("no choice\n");
                return;
        }
    }while(choice != 'x');
}


int main()
{

    main_menu();

    return 0;
}
