#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Flashcard
{
    char word[100];
    char definition[100];

};

//create new set file (title.txt) and add title to set_list
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
        printf("<<Error open file>>");
        return;
        }

        fprintf(master,"%s\n",title);

        fclose(fp);
        fclose(master);
    }

}

//add card to set
int AddCard(char *title)
{
    char w[100];
    char d[100];
    char file_name[50];

    sprintf(file_name,"%s.txt",title);

    FILE *fp = fopen(file_name,"a");
    if(fp == NULL)
    {
        printf("<<Error open file>>");
        return 101;
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

//print all cards in the set
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
        printf("%s",str);
    }
    fclose(fp);
}

//print all list
int SetList()
{
    char str[200];
    int count = 1;
    FILE *fp = fopen("set_list.txt","r");
    if(fp == NULL)
    {
        printf("<<Error open file>>");
        return 101;
    }
    while(fgets(str,100,fp)!= NULL)
    {
        printf("%d. %s",count,str);
        count++;
    }
    fclose(fp);
}
void manage_card_menu(char *title)
{
    char choice;

    do
    {
        system("cls");
        printf("----------%s----------\n",title);
        CardInSet(title);
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
                manage_card_menu(title);
                break;
            case 'd': printf("Delete set"); break;
            case 'x': return;
            default:

                printf("no choice\n");
        }
    }while (choice != 'x');
}
void manage_set_menu()
{
    char choice;
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
                manage_set_menu();
                break;
            case 'd': printf("Delete set"); break;
            case 'm': manage_card_menu("Vocab"); break;
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
            case '2': manage_set_menu(); break;
            case 'x': return;
            default:
                printf("no choice\n");
                return;
        }
    }while(choice != 'x');
}


int main()
{
    //char title[] = "Alphabet";
    //AddSet();
    //SetList();
    main_menu();
    //AddCard(title);
    //CardInSet(title);

    return 0;
}
