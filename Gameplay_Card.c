#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

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
int AddSet(char *buffer)
{
    char file_name[50];
    char title[50];

    while (1)
    {
        system("cls");
        printf("Enter title (max %d chars, or 0 to go back): ", (int)sizeof(title)-1);

        fgets(title, sizeof(title), stdin);
        trimNewline(title);

        if (strcmp(title, "0") == 0)
            return 0;

        if (strlen(title) == 0)
        {
            printf("\n[Error] Empty input is not allowed!\n");
            Sleep(1000);
            continue;
        }

        if (strlen(title) >= sizeof(title))
        {
            printf("\n[Error] Title too long! Maximum %d characters.\n",
                   (int)sizeof(title)-1);
            Sleep(1000);
            continue;
        }
        else break;
    }

    sprintf(file_name, "%s.txt", title);

    FILE *fp = fopen(file_name, "w");
    FILE *master = fopen("set_list.txt", "a");

    if (fp == NULL || master == NULL)
    {
        printf("<Error opening file>");
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
    char file_name[50];

    sprintf(file_name, "%s.txt", title);

    FILE *fp = fopen(file_name, "a");
    if (fp == NULL)
    {
        printf("<Error opening file>");
        return 1;
    }

    system("cls");

    while (1)
    {
        printf("Enter word (max %d chars, or 0 to back): ", (int)sizeof(w)-1);
        gets(w);

        if (strcmp(w, "0") == 0)
            break;

        if (strlen(w) == 0)
        {
            printf("[Error] Empty is not allowed.\n");
            Sleep(800);
            continue;
        }

        if (strlen(w) >= sizeof(w))
        {
            printf("[Error] Word too long! Maximum %d characters.\n",
                   (int)sizeof(w)-1);
            Sleep(800);
            continue;
        }

        printf("Enter definition (max %d chars, or 0 to back): ", (int)sizeof(d)-1);
        gets(d);

        if (strcmp(d, "0") == 0)
            break;

        if (strlen(d) == 0)
        {
            printf("[Error] Empty is not allowed.\n");
            Sleep(800);
            continue;
        }

        if (strlen(d) >= sizeof(d))
        {
            printf("[Error] Definition too long! Maximum %d characters.\n",
                   (int)sizeof(d)-1);
            Sleep(800);
            continue;
        }

        fprintf(fp, "%s:%s\n", w, d);
    }

    fclose(fp);
    return 0;
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
        printf("%d. %s",count,str);
        count++;
    }

    fclose(fp);
}

void card_menu(char *title)
{
    char choice,confirm;
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
        printf("======== %s ========\n",title);
        CardList(title);
        printf("\n");
        printf("[A] Add card\n");
        printf("[D] Delete card\n");
        printf("[X] Back\n");
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
                        printf("[Error]: Card number %d not found\n",lineNum);
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

void set_menu()
{
    char choice,confirm;
    char setName[100];
    int lineNum;

    do
    {
        system("cls");
        printf("======== Flashcard Sets ========\n");
        SetList();
        printf("\n");
        printf("[A] Add set\n");
        printf("[D] Delete set\n");
        printf("[M] Manage set\n");
        printf("[X] Back\n");
        printf("\nSelect an option: ");
        choice = _getch();
        printf("%c\n",choice);
        choice = tolower(choice);

        switch(choice)
        {
            case 'a':
                if (AddSet(setName) == 1)
                    card_menu(setName);
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
                        printf("[Error]: Set number %d not found\n",lineNum);
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
                            card_menu(setName);
                        break;
                    }
                    else
                    {
                        printf("[Error]: Set number %d not found\n",lineNum);
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

void main_menu()
{
    char choice;

    do
    {
        system("cls");
        printf("[1] Start\n");
        printf("[2] Manage Sets\n");
        printf("[X] Close Program\n");

        choice = _getch();
        printf("%c",choice);
        choice = tolower(choice);

        switch(choice)
        {
            case '1':
                printf("Starting game...\n");
                Sleep(1000);
                break;

            case '2': set_menu(); break;

            case 'x': return;

            default :
                printf("\n Invalid choice! Please try again.\n");
                Sleep(1000);
        }
    }while(choice != 'x');
}


///////////////////////////////////////////////////////////////////


struct Flashcard
{
    char word[100];
    char definition[100];
};


int LoadDeck(char *setName, struct Flashcard *deck)
{
    char file_name[100];
    char line[250];
    int count = 0;

    sprintf(file_name, "%s.txt", setName);
    FILE *fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        printf("<Error open file>");
        return 0;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {

        trimNewline(line);

        char *token_word = strtok(line, ":");
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
    options[0] = deck[currentIdx];

    int usedIdx[4];
    usedIdx[0] = currentIdx;

    for (int i = 1; i < 4; i++)
    {
        int randIdx;
        int isDuplicate;

        do {
            randIdx = rand() % count;
            isDuplicate = 0;
            for(int j=0; j<i; j++) {
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
    for (int i = 3; i > 0; i--)
    {
        int j = rand() % (i + 1);

        int temp = indices[i];
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


void PlayRPG(struct Flashcard *deck, int count)
{
    if (count < 4)
    {
        printf("\n [Error] Not enough cards! Need at least 4 cards to play Choice Mode.\n");
        Sleep(2000);
        return;
    }

    int playerHP = 3;
    int bossHP = count;
    int maxHP = 4;
    int MaxbossHP = count;
    int score = 0;

    struct Flashcard options[4];
    int correctIdx;

    for (int i = 0; i < count; i++)
    {
        if (playerHP <= 0) break;

        GenerateOptions(deck, count, i, options, &correctIdx);

        system("cls");
        printf("========================================\n");
        printf(" WAVE %d/%d   |   SCORE: %d\n", i+1, count, score);
        printf("========================================\n");

        printf(" HP: ");
        for(int h=0; h<maxHP; h++) {
            if(h < playerHP) printf("O");
            //else printf("XX ");
        }
        printf("%20s"," HP : ");
        for(int h=0; h<MaxbossHP; h++)
        {
            if(h < bossHP) printf("O");
            //else printf("XX ");
        }

        printf("\n========================================\n\n");

        printf("       /\\_/\\ \n");
        printf("      ( O.O )   < \"Answer me!\"\n");
        printf("       > ^ < \n\n");

        printf(" Question: [ %s ]\n\n", deck[i].word);

        printf(" [1] %s\n", options[0].definition);
        printf(" [2] %s\n", options[1].definition);
        printf(" [3] %s\n", options[2].definition);
        printf(" [4] %s\n", options[3].definition);

        int selected;

        while(1)
        {
           printf("\n Select answer (1-4): ");

            char key = _getch();
            selected = -1;

            if(key >= '1' && key <= '4')
            {
                selected = key - '1';
                break;
            }
            else
            {
                printf("not in choice");
            }
        }

        if (selected == correctIdx)
        {
            printf("\n\n >>> Correct! Critical Hit! <<<\n");
            score++;
            if(playerHP < maxHP) playerHP++;
            bossHP--;
        }
        else
        {
            printf("\n\n >>> WRONG! You took damage! <<<\n");
            printf(" Correct answer was: [%d] %s\n", correctIdx+1, deck[i].definition);
            playerHP--;
        }

        Sleep(1500);
    }

    system("cls");
    printf("========================================\n");

    if (playerHP > 0) {
        printf("       VICTORY! \n");
        printf(" You cleared the dungeon!\n");
    } else {
        printf("       GAME OVER \n");
        printf(" Better luck next time...\n");
    }
    printf(" Final Score: %d / %d\n", score, count);
    printf("========================================\n");
    printf(" Press any key to return...");
    _getch();
}

void StartGame(char *setName)
{
    struct Flashcard deck[100];
    int totalCards;

    system("cls");
    printf("Loading deck: %s...\n", setName);

    totalCards = LoadDeck(setName, deck);

    if (totalCards == 0) {
        printf(" [Error] No cards found!\n");
        Sleep(2000);
        return;
    }

    ShuffleDeck(deck, totalCards);

    PlayRPG(deck, totalCards);
}

int main()
{
    StartGame("Vocab");
    return 0;
}

