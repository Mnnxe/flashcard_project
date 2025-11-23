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
int AddSet(char *buffer)
{
    char file_name[100];
    char title[100];
    int MAX_LEN = 50;

    while(1)
    {
        system("cls");
        printf("Enter title (max %d chars) or enter 0 to go back: ", MAX_LEN);
        gets(title);

        if(strcmp(title, "0") == 0)
            return 0;

        if(strlen(title) == 0)
        {
            printf("\n[!] Empty input is not allowed.\n");
            Sleep(1200);
        }
        else if(strlen(title) > MAX_LEN)
        {
            printf("\n[!] Title is too long! Maximum is %d characters.\n", MAX_LEN);
            Sleep(1200);
        }
        else
            break;
    }

    sprintf(file_name, "%s.txt", title);

    FILE *fp = fopen(file_name, "w");
    FILE *master = fopen("set_list.txt", "a");

    if(fp == NULL || master == NULL)
    {
        printf("<File Error>");
        return 0;
    }

    fprintf(master, "%s\n", title);

    fclose(fp);
    fclose(master);

    strcpy(buffer, title);
    return 1;
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

    remove(file_name);
    remove("set_list.txt");
    rename("temp_file.txt","set_list.txt");

    printf("\nDeleted successfully.\n ");
    Sleep(1000);
}

int AddCard(char *title)
{
    char w[100];
    char d[100];
    char file_name[100];
    int MAX_LEN = 50;

    sprintf(file_name, "%s.txt", title);

    FILE *fp = fopen(file_name, "a");
    if(fp == NULL)
    {
        printf("<File Error>");
        return 1;
    }

    system("cls");

    while(1)
    {
        printf("Enter word (max %d chars) (or enter 0 to go back): ", MAX_LEN);
        fgets(w,sizeof(w),stdin);
        trimNewline(w);

        if(strcmp(w, "0") == 0)
            break;

        if(strlen(w) == 0)
        {
            printf("\n[!] Empty input is not allowed.\n");
            Sleep(1000);
            continue;
        }
        else if(strlen(w) > MAX_LEN)
        {
            printf("\n[!] Word is too long! Maximum is %d characters.\n", MAX_LEN);
            Sleep(1000);
            continue;
        }

            while(1)
            {
                printf("Enter definition (max %d chars) (or enter 0 to cancel): ", MAX_LEN);
                fgets(d,sizeof(d),stdin);
                trimNewline(d);

                if(strcmp(d, "0") == 0)
                    return 0;

                if(strlen(d) == 0)
                {
                    printf("\n[!] Empty input is not allowed.\n");
                    Sleep(1000);
                    continue;
                }
                else if(strlen(d) > MAX_LEN)
                {
                    printf("\n[!] Definition is too long! Maximum is %d characters.\n", MAX_LEN);
                    Sleep(1000);
                    continue;
                }
                else break;
            }
        fprintf(fp, "%s:%s\n", w, d);
    }


    fclose(fp);
    return 1;
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

    printf("\nDeleted successfully.\n ");
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
        printf("  %d. %s",count,str);
        count++;
    }

    fclose(fp);
}

void CardMenu(char *title)
{
    char choice,confirm;
    char file_name[100];
    char card[200];
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
        printf("======== %s ========\n",title);
        CardList(title);
        printf("\n");
        printf("\n[A]Add  [D]Delete  [X]Back ");
        printf("\nSelect an option: ");
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
                    printf("Enter line number to delete(0 to cancel): ");
                    if(scanf("%d",&lineNum)!=1)
                    {
                        clearBuffer();
                        printf("\n Invalid input! Please try again.\n");
                        Sleep(1000);
                        continue;
                    }
                    clearBuffer();
                    if(lineNum == 0)
                    {
                        printf(">Canceled<");
                        Sleep(1000);
                        break;
                    }
                    if(GetLine(lineNum,title,card) == 1)
                    {
                        printf("Are you sure you want to delete? (y/n): ");
                        confirm = _getch();
                        printf("%c\n",confirm);
                        if(confirm == 'y')
                        {
                            DelCard(card,file_name);
                        }
                        else
                        {
                            printf(">Canceled<");
                            fflush(stdout);
                            Sleep(1000);
                        }
                        break;

                    }
                    else
                    {
                        printf("[!]: Card number %d not found\n",lineNum);
                        Sleep(1200);
                    }
                }
                break;

            case 'x': return;

            default:
                printf("\n Invalid input! Please try again.\n");
                Sleep(1000);
        }
    }while (choice != 'x');
}

void RunSetMenu()
{
    char choice,confirm;
    char setName[100];
    int lineNum;

    do
    {
        system("cls");
        printf("========================= Flashcard Sets =========================\n");
        SetList();
        printf("\n\n");
        printf("     [A]Add  [D]Delete  [M]Manage  [X]Exit\n\n");
        printf("     Select an option: ");
        choice = _getch();
        printf("%c\n",choice);
        choice = tolower(choice);

        switch(choice)
        {
            case 'a':
                if (AddSet(setName) == 1)
                    CardMenu(setName);
                break;

            case 'd':
                while(1)
                {

                    printf("Enter line number to delete(0 to cancel): ");
                    if(scanf("%d",&lineNum)!=1)
                    {
                        clearBuffer();
                        printf("\n Invalid input! Please try again.\n");
                        Sleep(1000);
                        continue;
                    }
                    clearBuffer();
                    if(lineNum == 0)
                    {
                        printf(">Canceled<");
                        Sleep(1000);
                        break;
                    }
                    if(GetLine(lineNum,"set_list",setName) == 1)
                    {
                        printf("Are you sure you want to delete? (y/n): ");
                        confirm = _getch();
                        printf("%c\n",confirm);
                        if(confirm == 'y')
                        {
                            DelSet(setName);
                        }
                        else
                        {
                            printf(">Canceled<");
                            fflush(stdout);
                            Sleep(1000);
                        }
                        break;
                    }
                    else
                    {
                        printf("[!]: Set number %d not found\n",lineNum);
                        Sleep(1200);
                    }
                }
                break;

            case 'm':
                while(1)
                {
                    printf("Enter line number to manage(0 to cancel): ");
                    if(scanf("%d",&lineNum)!=1)
                    {
                        clearBuffer();
                        printf("\n Invalid input! Please try again.\n");
                        Sleep(1000);
                        continue;
                    }
                    clearBuffer();
                    if(lineNum == 0)
                    {
                        printf(">Canceled<");
                        Sleep(1000);
                        break;
                    }
                    if(GetLine(lineNum,"set_list",setName) == 1)
                    {
                            CardMenu(setName);
                        break;
                    }
                    else
                    {
                        printf("[!]: Set number %d not found\n",lineNum);
                        Sleep(1200);
                    }
                }
                break;

            case 'x': return;

            default:
                printf("\n Invalid choice! Please try again.\n");
                Sleep(1000);
        }
    }while (choice != 'x');

}

//Learn

//Game
int LoadDeck(char *setName, struct Flashcard *deck)
{
    char file_name[100];
    char str[250];
    int count = 0;

    sprintf(file_name, "%s.txt", setName);
    FILE *fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        printf("<Error open file>");
        return 0;
    }

    while (fgets(str, sizeof(str), fp) != NULL)
    {

        trimNewline(str);

        char *token_word = strtok(str, ":");
        char *token_def = strtok(NULL, ":");

        if (token_word != NULL && token_def != NULL)
        {
            strcpy(deck[count].word, token_word);
            strcpy(deck[count].definition, token_def);
            count++;
        }

        if (count >= 100) break;
    }

    fclose(fp);
    return count;
}

void ShuffleDeck(struct Flashcard *deck, int count)
{
    srand(time(NULL));
    for (int i = count - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        struct Flashcard temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}


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
        printf("               ###### ######    #####   ##     ##    ##    ##   #####   ##     ##      #####   ##    ##\n");
        printf("               ##     ##    # ##     ## ###   ###    ###   ## ##     ## ##  #  ##    ##     ## ###   ##\n");
        printf("               ###### ######  ##     ## ## ### ##    ## ## ## ##     ## ## ### ##    ##     ## ## ## ##\n");
        printf("               ##     ##  ##  ##     ## ##  #  ##    ##   ### ##     ## ###   ###    ##     ## ##   ###\n");
        printf("               ##     ##   ##   #####   ##     ##    ##    ##   #####   ##     ##      #####   ##    ##\n");

        printf("\n");
        printf("    ######  ###### ##    #####       ###       ##    ##  ######  ##     ##      ######      ###   ##     ##  ##    ##\n");
        printf("      ##      ##   ##   ##         ##   ##     ###   ##  ##      ##  #  ##      ##    #   ##   ## ##  #  ##  ###   ##\n");
        printf("      ##      ##         #####     #######     ## ## ##  ######  ## ### ##      ##     #  ####### ## ### ##  ## ## ##\n");
        printf("      ##      ##             ##    ##   ##     ##   ###  ##      ###   ###      ##    #   ##   ## ###   ###  ##   ###\n");
        printf("    ######    ##         #####     ##   ##     ##    ##  ######  ##     ##      ######    ##   ## ##     ##  ##    ##\n");

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
        printf("%50s[1] Start Game\n"," ");
        printf("%50s[2] Learn Flashcard\n"," ");
        printf("%50s[3] Manage Flashcard\n"," ");
        printf("%50s[X] Close Program\n"," ");

        printf("%48s>>"," ");
        choice = _getch();
        printf("%c",choice);
        choice = tolower(choice);

        switch(choice)
        {
            case '1':
                while(1)
                {
                    system("cls");
                    printf("==========Which set you want to play?===========\n");
                    SetList();

                    printf("\nEnter line number(0 to cancel): ");
                    if(scanf("%d",&lineNum)!=1)
                    {
                        clearBuffer();
                        printf("\n Invalid input! Please try again.\n");
                        Sleep(1000);
                        continue;
                    }
                    clearBuffer();
                    if(lineNum == 0)
                    {
                        printf(">Canceled<");
                        Sleep(1000);
                        break;
                    }
                    if(GetLine(lineNum,"set_list",setName) == 1)

                    {
                        printf(">> %s is selected, You want to continue?(y/n): ",setName);
                        confirm = _getch();
                        printf("%c\n",confirm);
                        if(confirm == 'y')
                        {
                            //StartGame(setName);
                            break;
                        }
                        else
                        {
                            printf(">Canceled<");
                            fflush(stdout);
                            Sleep(1000);
                        }
                        break;
                    }
                    else
                    {
                        printf("[!]: Set number %d not found\n",lineNum);
                        Sleep(1200);
                    }
                    break;
                }

            case '2': printf("Learn"); break;

            case '3': RunSetMenu(); break;

            case 'x': return 0;

            default :
                printf("\n [!]Invalid input! Please try again.\n");
                Sleep(1000);
        }
    }while(choice != 'x');
    return 0;
}
