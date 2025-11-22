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

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ClearBottom(int y) {
    gotoxy(0, y);
    for(int i = 0; i < 15; i++)
    {
        printf("                                                                                \n");
    }
    gotoxy(0, y); // กลับมารอที่เดิม
}

//file management function
int AddSet(char *buffer)
{
    char file_name[50];
    char title[50];

    while (1)
    {
        system("cls");
        printf("Enter title (max %d chars, or 0 to go back): ",(int)sizeof(title)-1);

        fgets(title,sizeof(title),stdin);
        trimNewline(title);

        if (strcmp(title,"0") == 0)
            return 0;

        if (strlen(title) == 0)
        {
            printf("\n[Error] Empty input is not allowed!\n");
            Sleep(1000);
            continue;
        }

        if (strlen(title) >= sizeof(title))
        {
            printf("\n[Error] Title too long! Maximum %d characters.\n",sizeof(title)-1);
            Sleep(1000);
            continue;
        }

        else break;
    }

    sprintf(file_name, "%s.txt",title);

    FILE *fp = fopen(file_name,"w");
    FILE *master = fopen("set_list.txt","a");

    if (fp == NULL || master == NULL)
    {
        printf("<Error opening file>");
        return 0;
    }

    fprintf(master,"%s\n",title);

    fclose(fp);
    fclose(master);

    strcpy(buffer,title);
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

    printf("\nDeleted successfully.\n");
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

    printf("\nDeleted successfully.\n");
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
                    if(scanf("%d",&lineNum) != 1)
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
                        printf("<Canceled>");
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
                            printf("<Canceled>");
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



//Q&A function

struct Flashcard
{
    char word[100];
    char definition[100];
};


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

int GetAns()
{
    int selected = -1;
    char key;
    while(1)
        {
            printf("Attack (1-4): ");
            key = _getch();
            if(key >= '1' && key <= '4')
            {
                selected = key - '1';
                break;
            }
            else
            {
                gotoxy(0,19);
                printf("[Error] Invalid input.");
                Sleep(1500);
                gotoxy(0, 19);
                printf("                                   ");
                gotoxy(0,18);

            }
        }
    return selected;
}

//RPG MODE
void CalculateBossHP(int count, int *tierHP)
{
    tierHP[1] = (count * 15) / 100;
    if(tierHP[1] < 1) tierHP[1] = 1;

    tierHP[2] = (count * 20) / 100;
    if(tierHP[2] < 1) tierHP[2] = 1;

    tierHP[3] = (count * 30) / 100;
    if(tierHP[3] < 1) tierHP[3] = 1;

    tierHP[4] = count - (tierHP[1] + tierHP[2] + tierHP[3]);
    if (tierHP[4] < 1) tierHP[4] = 1;

}


void Monster(int currentTier)
{
    //random boss
        if(currentTier == 1)
        {
            printf("       /o..o\\  [ Dialog ]\n");
            printf("      ( >_< )  [  Name  ]\n");
        }
        else if(currentTier == 2)
        {
            printf("       /|  |\\  [ Dialog ]\n");
            printf("      ( O_O )  [  Name  ]\n");
        }
        else if(currentTier == 3)
        {
            printf("      /|__o__|\\  [ Dialog ]\n");
            printf("     (  > _ <  ) [  Name  ]\n");
        }
        else
        {
            printf("     <`|\\_//|`>  [ Dialog ]\n");
            printf("      ( @ A @ )  [  Name  ]\n");
        }
}
void ClearBoss()
{
    int i;
    gotoxy(0,6);
    for(i=0;i<4;i++)
    {
        printf("                                                               \n");
    }
}

void Scene(int currentTier,int currentBossHP,int currentBossMaxHP,int playerHP, int playerMaxHP,int score)
{
    system("cls");

    printf("========================================\n");

    if (currentTier == 4) printf(" >> FINAL BOSS << ");
    else printf(" LEVEL %d / 4      ", currentTier);

    printf("|   SCORE: %d\n", score);
    printf("========================================\n");
    printf(" BOSS: \n");
    printf("  YOU: \n");
    printf("========================================\n\n");

    Monster(currentTier); // วาดมอนสเตอร์ (ประมาณบรรทัด 8-13)

    printf("\n========================================\n");
}


void UpdateStats(int currentBossHP, int currentBossMaxHP, int playerHP, int playerMaxHP, int score)
{
    int bars;
    int h;

    //update score
    gotoxy(29, 1);
    printf("%d    ", score);

    //update boss hp
    gotoxy(7,3);
    if (currentBossHP > 10)
    {
        bars = 10;
    }
    else
    {
        bars = currentBossHP;
    }

    for(int h=0; h<bars; h++)
        if(h<bars)
            printf("#"); // เขียนทับขีดเดิม
        else
            printf(" ");

    printf(" [%d/%d]   ", currentBossHP, currentBossMaxHP); // เติมช่องว่างท้ายกันเลขค้าง

    //update player hp
    gotoxy(7,4);
    for(int h=0; h < playerMaxHP; h++) {
        if(h < playerHP)
            printf("O");
        else
            printf("X");
    }
}
void PlayRPG(struct Flashcard *deck, int count)
{
    if(count < 4)
    {
        printf("\n [Error] Not enough cards! Need at least 4 cards.\n");
        Sleep(2000);
        return;
    }

    int tierHP[5];
    CalculateBossHP(count,tierHP);

    int currentTier = 1;
    int currentBossMaxHP = tierHP[1];
    int currentBossHP = tierHP[1];

    int playerHP = count/3;
    int playerMaxHP = count/3;
    int remaining = count;
    int score = 0;

    struct Flashcard options[4];
    int correctIdx;
    int currentIdx;

    int selected;

    Scene(currentTier,currentBossHP,currentBossMaxHP,playerHP,playerMaxHP,score);

    while (remaining > 0 && playerHP > 0)
    {
        currentIdx = rand() % remaining;
        GenerateOptions(deck, count, currentIdx, options, &correctIdx);

        UpdateStats(currentBossHP,currentBossMaxHP,playerHP,playerMaxHP,score);

        ClearBottom(11);

        printf(" Question: [ %s ]\n\n", deck[currentIdx].word);
        printf(" [1] %s\n", options[0].definition);
        printf(" [2] %s\n", options[1].definition);
        printf(" [3] %s\n", options[2].definition);
        printf(" [4] %s\n", options[3].definition);

        printf("\n");

        selected = GetAns();

        if (selected == correctIdx)
        {
            printf("\n\n >>> CRITICAL HIT! <<<\n");
            score++;
            currentBossHP--;
            remaining--;
            SwapCards(&deck[currentIdx], &deck[remaining]);

            if (currentBossHP <= 0 && remaining > 0)
            {
                ClearBoss();
                currentTier++;
                currentBossMaxHP = tierHP[currentTier];
                currentBossHP = currentBossMaxHP;

                if(playerHP < playerMaxHP)
                    playerHP++;

                ClearBottom(11);
                printf("\n *** LEVEL CLEARED! BOSS EVOLVED! ***\n");
                Sleep(1500);
                ClearBottom(11);

                gotoxy(0,11);
                printf("[Cutscene]\n\n");
                printf("[Item]\n");

                printf("\nPress any key to continue...");
                _getch();
                Scene(currentTier,currentBossHP,currentBossMaxHP,playerHP,playerMaxHP,score);
                continue;
            }
        }
        else
        {
            printf("\n\n >>> MISS! You took damage! <<<\n");
            printf(" Correct: [%d] %s\n", correctIdx+1, deck[currentIdx].definition);
            playerHP--;
        }

        Sleep(1200);
    }

    //Result
    system("cls");
    printf("========================================\n");
    if(playerHP > 0)
    {
        printf("       VICTORY! \n");
        printf("========================================\n");
        printf(" You defeated all monsters!\n");
    }
    else
    {
        printf("       GAME OVER \n");
        printf("========================================\n");
        if (currentTier == 4) printf(" You fell to the Dragon...\n");
        else printf(" You fell at Level %d\n", currentTier);
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
    printf("Loading deck: %s...\n",setName);
    Sleep(1000);

    totalCards = LoadDeck(setName,deck);

    if (totalCards == 0)
    {
        printf("[Error] No cards found!\n");
        Sleep(2000);
        return;
    }
    else if(totalCards < 4)
    {
        printf("[Error] Must have at least 4 card in the set!\n");
        Sleep(2000);
        return;
    }

    ShuffleDeck(deck,totalCards);
    PlayRPG(deck,totalCards);
}

int main()
{
    StartGame("Vocab");
}

