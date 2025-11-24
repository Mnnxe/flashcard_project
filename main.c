#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

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
    char str[200];
    char file_name[100];

    sprintf(file_name,"%s.txt",name);

    FILE *fp = fopen(file_name,"r");
    if(fp == NULL)
    {
        printf("\t\t\t< File is empty >");
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
void AddSet(char *title)
{
    char file_name[100];

    sprintf(file_name, "%s.txt", title);

    FILE *fp = fopen(file_name, "w");
    FILE *master = fopen("set_list.txt", "a");

    if(fp == NULL || master == NULL)
    {
        printf("\t\t\t< File is empty >");
    }

    fprintf(master, "%s\n", title);

    fclose(fp);
    fclose(master);

    return;
}


void DelSet(char *title)
{
    char str[50];
    char file_name[100];

    sprintf(file_name,"%s.txt",title);

    FILE *fp = fopen("set_list.txt","r");
    FILE *tp = fopen("temp_file.txt","w");

    if(fp == NULL || tp == NULL)
    {
        printf("\t\t\t< File is empty >");
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

    remove(file_name);
    remove("set_list.txt");
    rename("temp_file.txt","set_list.txt");

    printf("\n\t\t\tDeleted successfully.\n ");
    Sleep(1000);
    return;
}

void EditSetTitle(char *old_title)
{
    int MAX_LEN = 50;
    char str[50];
    char new_title[100];
    char old_file[100];
    char new_file[100];

    while(1)
    {
        printf("\n\t\t\tEnter new title (max %d chars) or enter 0 to go back: ", MAX_LEN);
        gets(new_title);

        if(strcmp(new_title, "0") == 0)
            return;

        if(strlen(new_title) == 0)
        {
            printf("\t\t\t\n[!] Empty input is not allowed.\n");
            Sleep(1200);
        }
        else if(strlen(new_title) > MAX_LEN)
        {
            printf("\n\t\t\t[!] Title is too long! Maximum is %d characters.\n", MAX_LEN);
            Sleep(1200);
        }
        else
            break;
    }

    sprintf(old_file,"%s.txt",old_title);
    sprintf(new_file,"%s.txt",new_title);

    FILE *fp = fopen("set_list.txt","r");
    FILE *op = fopen(old_file,"r");
    FILE *tp = fopen("temp_file.txt","w");

    if(fp == NULL || op == NULL || tp == NULL)
    {
        printf("\t\t\t< File is empty >");
    }

    while(fgets(str,sizeof(str),fp) != NULL )
    {
        trimNewline(str);

        if(strcmp(str,old_title) != 0)
        {
            fprintf(tp,"%s\n",str);
        }
        else
        {
            fprintf(tp,"%s\n",new_title);
        }
    }

    fclose(fp);
    fclose(tp);
    fclose(op);

    remove(old_file);
    remove("set_list.txt");
    rename("temp_file.txt","set_list.txt");
    rename(old_file,new_file);

    printf("\n\t\t\tName changed successfully.\n ");
    Sleep(1000);
}

void AddCard(char *title)
{
    char w[100];
    char d[100];
    char file_name[100];
    int MaxLen = 50;

    sprintf(file_name, "%s.txt", title);

    FILE *fp = fopen(file_name, "a");
    if(fp == NULL)
    {
        printf("\t\t\t< File is empty >");
    }

    system("cls");

    while(1)
    {
        printf("\t\t\tEnter word (max %d chars) (or enter 0 to go back): ", MaxLen);
        fgets(w,sizeof(w),stdin);
        trimNewline(w);

        if(strcmp(w, "0") == 0)
            break;

        if(strlen(w) == 0)
        {
            printf("\n\t\t\t[!] Empty input is not allowed.\n");
            Sleep(1000);
            continue;
        }
        else if(strlen(w) > MaxLen)
        {
            printf("\n\t\t\t[!] Word is too long! Maximum is %d characters.\n", MaxLen);
            Sleep(1000);
            continue;
        }

            while(1)
            {
                printf("\t\t\tEnter definition (max %d chars) (or enter 0 to cancel): ", MaxLen);
                fgets(d,sizeof(d),stdin);
                trimNewline(d);

                if(strcmp(d, "0") == 0)
                    return;

                if(strlen(d) == 0)
                {
                    printf("\n\t\t\t[!] Empty input is not allowed.\n");
                    Sleep(1000);
                    continue;
                }
                else if(strlen(d) > MaxLen)
                {
                    printf("\n\t\t\t[!] Definition is too long! Maximum is %d characters.\n", MaxLen);
                    Sleep(1000);
                    continue;
                }
                else break;
            }
        fprintf(fp, "%s:%s\n", w, d);
    }


    fclose(fp);
    return;
}

void DelCard(char *word,char *title)
{
    char str[100];
    char file_name[50];

    sprintf(file_name,"%s.txt",title);
    FILE *fp = fopen(file_name,"r");
    FILE *tp = fopen("temp_file.txt","w");

    if(fp == NULL || tp == NULL)
    {
        printf("\t\t\t< File is empty >");
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

    remove(file_name);
    rename("temp_file.txt",file_name);

    printf("\n\t\t\tDeleted successfully.\n ");
    Sleep(1000);
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
        printf("\t\t\t< File is empty >");
    }

    while(fgets(str,sizeof(str),fp)!= NULL)
    {
        printf("\t\t\t%3d. %s",count,str);
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
        printf("\t\t\t< File is empty >");
        //return 0;
    }

    while(fgets(str,100,fp)!= NULL)
    {
        printf("\t\t\t%3d. %s",count,str);
        count++;
    }

    fclose(fp);
}

void CardMenu(char *title)
{
    char choice,confirm;
    char card[200];
    int lineNum;

    do
    {
        system("cls");
        printf("\t\t\t========================= %s =========================\n\n",title);
        CardList(title);
        printf("\n");
        printf("\n\t\t\t[A]Add  [D]Delete  [X]Back ");
        printf("\n\t\t\tSelect an option: ");
        choice = _getch();
        printf("%c\n",choice);
        choice = tolower(choice);

        switch(choice)
        {
            case 'a':
                AddCard(title);
                system("cls");
                break;

            case 'd':
                while(1)
                {
                    printf("\t\t\tEnter line number to delete(0 to cancel): ");
                    if(scanf("%d",&lineNum)!=1)
                    {
                        clearBuffer();
                        printf("\t\t\t[!] Invalid input! Please try again.\n");
                        Sleep(1000);
                        continue;
                    }
                    clearBuffer();
                    if(lineNum == 0)
                    {
                        printf("\t\t\t> Canceled <");
                        Sleep(1000);
                        break;
                    }
                    if(GetLine(lineNum,title,card) == 1)
                    {
                        printf("\t\t\tAre you sure you want to delete? (y/n): ");
                        confirm = _getch();
                        printf("%c\n",confirm);
                        if(confirm == 'y')
                        {
                            DelCard(card,title);
                        }
                        else
                        {
                            printf("\t\t\t> Canceled <");
                            fflush(stdout);
                            Sleep(1000);
                        }
                        break;

                    }
                    else
                    {
                        printf("\t\t\t[!] Card number %d not found\n",lineNum);
                        Sleep(1200);
                    }
                }
                break;

            case 'x': return;

            default:
                printf("\t\t\t[!] Invalid input. Please try again.\n");
                Sleep(1000);
        }
    }while (choice != 'x');
}

void RunSetMenu()
{
    char choice,confirm;
    char setName[100];
    int lineNum;
    int MaxLen = 50;
    char manage;
    char new_title[100];

    do
    {
        system("cls");
        printf("\t\t\t========================= Flashcard Sets =========================\n\n");
        SetList();
        printf("\n\n");
        printf("\t\t\t[A]Add  [D]Delete  [M]Manage  [X]Exit\n\n");
        printf("\t\t\tSelect an option: ");
        choice = _getch();
        printf("%c\n",choice);
        choice = tolower(choice);

        switch(choice)
        {
            case 'a':
                while(1)
                {
                    printf("\t\t\tEnter title (max %d chars) or enter 0 to go back: ", MaxLen);
                    gets(setName);

                    if(strcmp(setName, "0") == 0)
                    break;

                    if(strlen(setName) == 0)
                    {
                        printf("\t\t\t\n[!] Empty input is not allowed.\n");
                        Sleep(1200);
                    }
                    else if(strlen(setName) > MaxLen)
                    {
                        printf("\n\t\t\t[!] Title is too long! Maximum is %d characters.\n", setName);
                        Sleep(1200);
                    }
                    else
                    {
                            AddSet(setName);
                            CardMenu(setName);
                        break;
                    }
                }
                break;

            case 'd':
                while(1)
                {

                    printf("\t\t\tEnter line number to delete(0 to cancel): ");
                    if(scanf("%d",&lineNum)!=1)
                    {
                        clearBuffer();
                        printf("\n\t\t\t[!] Invalid input. Please try again.\n");
                        Sleep(1000);
                        continue;
                    }
                    clearBuffer();
                    if(lineNum == 0)
                    {
                        printf("\t\t\t> Canceled <");
                        Sleep(1000);
                        break;
                    }
                    if(GetLine(lineNum,"set_list",setName) == 1)
                    {
                        printf("\t\t\tAre you sure you want to delete? (y/n): ");
                        confirm = _getch();
                        printf("%c\n",confirm);
                        if(confirm == 'y')
                        {
                            DelSet(setName);
                        }
                        else
                        {
                            printf("\t\t\t> Canceled <");
                            fflush(stdout);
                            Sleep(1000);
                        }
                        break;
                    }
                    else
                    {
                        printf("\t\t\t[!] Set number %d not found\n",lineNum);
                        Sleep(1200);
                    }
                }
                break;

            case 'm':
                while(1)
                {
                    printf("\t\t\tEnter line number to manage(0 to cancel): ");

                    if(scanf("%d",&lineNum)!=1)
                    {
                        clearBuffer();
                        printf("\n\t\t\t[!] Invalid input. Please try again.\n");
                        Sleep(1000);
                        continue;
                    }
                    clearBuffer();
                    if(lineNum == 0)
                    {
                        printf("\t\t\t> Canceled <");
                        Sleep(1000);
                        break;
                    }
                    if(GetLine(lineNum,"set_list",setName) == 1)
                    {
                        while(1)
                        {
                            printf("\t\t\tWhat do you want to do(0 to cancel)\n");
                            printf("\t\t\t  [1]Manage card in set\n");
                            printf("\t\t\t  [2]Change set name\n");
                            printf("\t\t\t>>");

                            manage = _getch();

                            if(manage == '1')
                            {
                                CardMenu(setName);
                                break;
                            }
                            else if(manage == '2')
                            {
                                EditSetTitle(setName);
                                break;
                            }
                            else if(manage == '0') break;
                            else printf("\n\t\t\t[!] Invalid input. Please try again.\n");

                        }
                        break;
                    }
                    else
                    {
                        printf("\t\t\t[!] Set number %d not found\n",lineNum);
                        Sleep(1200);
                    }
                }

                break;

            case 'x': return;

            default:
                printf("\n\t\t\t[!] Invalid input. Please try again.\n");
                Sleep(1000);
        }
    }while (choice != 'x');

}

//Learn
void GenerateOptions(struct Flashcard *deck, int count, int currentIdx, struct Flashcard *options, int *correctOptionIdx)
{
    int i,j,randIdx,isDuplicate,temp;

    options[0] = deck[currentIdx];

    int usedIdx[4];

    usedIdx[0] = currentIdx;

    for (int i = 1; i < 4; i++)
    {
        do {
            randIdx = rand() % count;
            isDuplicate = 0;
            for(j=0; j<i; j++) {
                if (randIdx == usedIdx[j]) {
                    isDuplicate = 1;
                    break;
                }
            }
        } while (isDuplicate);

        options[i] = deck[randIdx];
        usedIdx[i] = randIdx;
    }


    int indices[4] = {0, 1, 2, 3};
    for (i = 3; i > 0; i--)
    {
        j = rand() % (i + 1);

        temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    struct Flashcard tempOptions[4];

    for(int i=0; i<4; i++)
    {
        tempOptions[i] = options[indices[i]];

        if (indices[i] == 0)
        {
            *correctOptionIdx = i;
        }
    }


    for(int i=0; i<4; i++)
    {
        options[i] = tempOptions[i];
    }

}


void SwapCards(struct Flashcard *a, struct Flashcard *b) {
    struct Flashcard temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

//RPG MODE

void GameTitle()
{
    system("cls");
        printf("\n");
        printf("             ###### ######    #####   ##     ##    ##    ##   #####   ##     ##      #####   ##    ##\n");
        printf("             ##     ##    # ##     ## ###   ###    ###   ## ##     ## ##  #  ##    ##     ## ###   ##\n");
        printf("             ###### ######  ##     ## ## ### ##    ## ## ## ##     ## ## ### ##    ##     ## ## ## ##\n");
        printf("             ##     ##  ##  ##     ## ##  #  ##    ##   ### ##     ## ###   ###    ##     ## ##   ###\n");
        printf("             ##     ##   ##   #####   ##     ##    ##    ##   #####   ##     ##      #####   ##    ##\n");

        printf("\n");
        printf("    ###### ###### ##   #####       ###       ##    ## ###### ##     ##    ######     ###   ##     ## ##    ##\n");
        printf("      ##     ##   ##  ##         ##   ##     ###   ## ##     ##  #  ##    ##    #  ##   ## ##  #  ## ###   ##\n");
        printf("      ##     ##        #####     #######     ## ## ## ###### ## ### ##    ##     # ####### ## ### ## ## ## ##\n");
        printf("      ##     ##            ##    ##   ##     ##   ### ##     ###   ###    ##    #  ##   ## ###   ### ##   ###\n");
        printf("    ######   ##        #####     ##   ##     ##    ## ###### ##     ##    ######   ##   ## ##     ## ##    ##\n");

        printf("\n------------------------------------------------------------------------------------------------------------------------\n");
        printf("\n                                             RPG LERNING FLASHCARD GAME\n");
        printf("\n------------------------------------------------------------------------------------------------------------------------\n");
        printf("\n");
}
int main()
{
    char choice;
    int lineNum;
    char setName[100];
    char confirm;

    do
    {   GameTitle();
        printf("%46s[1] Start Game\n"," ");
        printf("%46s[2] Learn Flashcard\n"," ");
        printf("%46s[3] Manage Flashcard\n"," ");
        printf("%46s[X] Close Program\n"," ");

        printf("%46s>>"," ");
        choice = _getch();
        printf("%c",choice);
        choice = tolower(choice);

        switch(choice)
        {
            case '1':
                while(1)
                {
                    system("cls");
                    printf("\t\t\t========================= Which set you want to play =========================\n");
                    SetList();

                    printf("\n\t\t\tEnter line number(0 to cancel): ");
                    if(scanf("%d",&lineNum)!=1)
                    {
                        clearBuffer();
                        printf("\n\t\t\t[!] Invalid input. Please try again.\n");
                        Sleep(1000);
                        continue;
                    }
                    clearBuffer();
                    if(lineNum == 0)
                    {
                        printf("\t\t\t> Canceled <");
                        Sleep(1000);
                        break;
                    }
                    if(GetLine(lineNum,"set_list",setName) == 1)

                    {
                        printf("\t\t\t>> %s is selected, You want to continue?(y/n): ",setName);
                        confirm = _getch();
                        printf("%c\n",confirm);
                        if(confirm == 'y')
                        {
                            //StartGame(setName);
                            break;
                        }
                        else
                        {
                            printf("\t\t\t> Canceled <");
                            fflush(stdout);
                            Sleep(1000);
                        }
                        break;
                    }
                    else
                    {
                        printf("[!] Set number %d not found\n",lineNum);
                        Sleep(1200);
                    }
                    break;
                }

            case '2': printf("Learn"); break;

            case '3': RunSetMenu(); break;

            case 'x': return 0;

            default :
                printf("\n [!] Invalid input. Please try again.\n");
                Sleep(1000);
        }
    }while(choice != 'x');
    return 0;
}
