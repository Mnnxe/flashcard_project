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
            printf("\n[Error] Empty input is not allowed.\n");
            Sleep(1200);
        }
        else if(strlen(title) > MAX_LEN)
        {
            printf("\n[Error] Title is too long! Maximum is %d characters.\n", MAX_LEN);
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
            printf("\n[Error] Empty input is not allowed.\n");
            Sleep(1000);
            continue;
        }
        else if(strlen(w) > MAX_LEN)
        {
            printf("\n[Error] Word is too long! Maximum is %d characters.\n", MAX_LEN);
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
                    printf("\n[Error] Empty input is not allowed.\n");
                    Sleep(1000);
                    continue;
                }
                else if(strlen(d) > MAX_LEN)
                {
                    printf("\n[Error] Definition is too long! Maximum is %d characters.\n", MAX_LEN);
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
        printf("%d. %s",count,str);
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

void RunSetMenu()
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
        printf("\n[A]Add  [D]Delete  [M]Manage  [X]Exit\n");
        printf("\nSelect an option: ");
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
                            CardMenu(setName);
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

//story
//Story
void start_story()
{
    char c;
    int i;
    system("cls");
    char st0[500] = {"-------------------------------------------------------------------------------------------------------------------\n"};
    char st1[500] = {"\tA hundred years have passed since the Dawnfall, the day the sun refused to rise.\n"};

    char st2[500] = {"\tShadows stretched across the lands, and fear became constant.\n"};
    char st3[500] = {"\tCities crumbled, forests grew silent, and even the bravest forgot light.\n"};
    char st4[500] = {"\tHope became a whispered legend, barely remembered by those who survived.\n"};

    char st5[500] = {"\tThe world believes the dawn is gone forever, that light will never return and the night will never end.\n"};

    char st6[500] = {"\tBut tonight, a faint spark stirs - not in the sky, but within you.\n"};
    char st7[500] = {"\tA light long thought lost awakens, calling you to rise against the shadows.\n"};

    char st8[500] = {"\tBecause from now on..."};
    char st9[500] = {" it's a new dawn.\n"};
    char st10[500] = {"\tThe darkness trembles, "};
    char st11[500] = {"and the first step of your journey begins here.\n"};


    for(i=0; i<strlen(st0); i++)
    {
        c = st0[i];
        printf("%c",c);
        /*if(c=='.') Sleep(800);
        else Sleep(20);*/

    }

    for(i=0; i<strlen(st1); i++)
    {
        c = st1[i];
        printf("%c",c);
        if(c=='.') Sleep(800);
        else Sleep(20);

    }
    printf("\n");

    for(i=0; i<strlen(st2); i++)
    {
        c = st2[i];
        printf("%c",c);
        if(c=='.') Sleep(500);
        else Sleep(20);

    }

    for(i=0; i<strlen(st3); i++)
    {
        c = st3[i];
        printf("%c",c);
        if(c=='.') Sleep(500);
        else Sleep(20);

    }

    for(i=0; i<strlen(st4); i++)
    {
        c = st4[i];
        printf("%c",c);
        if(c=='.') Sleep(800);
        else Sleep(20);
    }
    printf("\n");

    for(i=0; i<strlen(st5); i++)
    {
        c = st5[i];
        printf("%c",c);
        if(c=='.') Sleep(800);
        else Sleep(20);
    }
    printf("\n");

    for(i=0; i<strlen(st6); i++)
    {
        c = st6[i];
        printf("%c",c);
        if(c==',') Sleep(400);
        if(c=='.') Sleep(500);
        else Sleep(20);

    }

    for(i=0; i<strlen(st7); i++)
    {
        c = st7[i];
        printf("%c",c);
        if(c=='.') Sleep(800);
        else Sleep(20);
    }
    printf("\n");

    for(i=0; i<strlen(st8); i++)
    {
        c = st8[i];
        printf("\033[1m%c\033[0m",c);
        //printf("",c);
        Sleep(20);
    }
    Sleep(1500);

    for(i=0; i<strlen(st9); i++)
    {
        c = st9[i];
        printf("\033[31m%c\033[0m",c);
        if(c=='.') Sleep(1000);
        else Sleep(20);

    }

    for(i=0; i<strlen(st10); i++)
    {
        c = st10[i];
        printf("%c",c);
        Sleep(20);

    }
    Sleep(1000);

    for(i=0; i<strlen(st11); i++)
    {
        c = st11[i];
        printf("\033[4m%c\033[0m",c);
        //if(c=='.') Sleep(1000);
        Sleep(20);

    }

    for(i=0; i<strlen(st0); i++)
    {
        c = st0[i];
        printf("%c",c);
        /*if(c=='.') Sleep(800);
        else Sleep(20);*/

    }

    Sleep(2000);
    printf("\n");

    printf("\t--- Press ENTER to continue ---");
    char co = _getch();

    if(co=='\r')
    {
        system("cls");
    }
}

void final_cut()
{
    char c;
    int i;

    system("cls");
    char st0[500] = {"-------------------------------------------------------------------------------------------------------------------\n"};
    char st1[500] = {"\tAs the final shadow collapses, darkness shatters and disperses into the air.\n"};
    char st2[500] = {"\tA warm, golden light rises from where the enemy fell, spreading across the land.\n"};

    char st3[500] = {"\tYou step forward, bathed in the glow of a new dawn, feeling hope return to every corner of the world.\n"};

    char st4[500] = {"\tAnd now,"};
    char st5[500] = {" the people look to the horizon with renewed hope,\n"};

    char st6[500] = {"\tas from now on... "};
    char st7[500] = {"it's a new dawn.\n"};

    for(i=0; i<strlen(st0); i++)
    {
        c = st0[i];
        printf("%c",c);

    }

    for(i=0; i<strlen(st1); i++)
    {
        c = st1[i];
        printf("%c",c);
        if(c=='.') Sleep(500);
        else Sleep(20);

    }

    for(i=0; i<strlen(st2); i++)
    {
        c = st2[i];
        printf("%c",c);
        if(c=='.') Sleep(800);
        else Sleep(20);

    }
    printf("\n");

    for(i=0; i<strlen(st3); i++)
    {
        c = st3[i];
        printf("%c",c);
        if(c==',') Sleep(400);
        if(c=='.') Sleep(500);
        else Sleep(20);
    }
    Sleep(1000);
    printf("\n");

    for(i=0; i<strlen(st4); i++)
    {
        c = st4[i];
        printf("\033[34m%c\033[0m",c);
        Sleep(20);
    }
    Sleep(800);

    for(i=0; i<strlen(st5); i++)
    {
        c = st5[i];
        printf("\033[34m%c\033[0m",c);
        Sleep(20);
    }
    Sleep(1000);
    printf("\n");

    for(i=0; i<strlen(st6); i++)
    {
        c = st6[i];
        printf("\033[1m%c\033[0m",c);
        Sleep(20);
    }
    Sleep(1500);

    for(i=0; i<strlen(st7); i++)
    {
        c = st7[i];
        printf("\033[1;32m%c\033[0m",c);
        if(c=='.') Sleep(1000);
        else Sleep(20);
    }

    for(i=0; i<strlen(st0); i++)
    {
        c = st0[i];
        printf("%c",c);
    }

    Sleep(2000);
    printf("\n");
}

void final_loss()
{
    char c;
    int i;

    char st0[500] = {"-------------------------------------------------------------------------------------------------------------------\n"};
    char st1[500] = {"\tYour final strike fades inches from the shadow’s heart.\n"};
    char st2[500] = {"\tThe world holds its breath as your light collapses in its grasp.\n"};
    char st3[500] = {"\tSo close... "};
    char st4[500] = {"the dawn was almost yours.\n"};

    for(i=0; i<strlen(st0); i++)
    {
        c = st0[i];
        printf("%c",c);
        /*if(c=='.') Sleep(800);
        else Sleep(20);*/

    }

    for(i=0; i<strlen(st1); i++)
    {
        c = st1[i];
        printf("%c",c);
        if(c=='.') Sleep(800);
        else Sleep(20);
    }

    for(i=0; i<strlen(st2); i++)
    {
        c = st2[i];
        printf("%c",c);
        if(c=='.') Sleep(800);
        else Sleep(20);
    }
    printf("\n");

    for(i=0; i<strlen(st3); i++)
    {
        c = st3[i];
        printf("\033[1m%c\033[0m",c);
        //printf("",c);
        Sleep(20);
    }
    Sleep(1500);

    for(i=0; i<strlen(st4); i++)
    {
        c = st4[i];
        printf("\033[1m%c\033[0m",c);
        Sleep(20);
    }

    for(i=0; i<strlen(st0); i++)
    {
        c = st0[i];
        printf("%c",c);
        /*if(c=='.') Sleep(800);
        else Sleep(20);*/

    }

    Sleep(2000);
    printf("\n");
}

//Character
typedef struct
{
    const char** art;
} Character;

Character c_swordsman;
Character c_sorcerer;
Character c_archer;
Character m_squid;
Character m_dino;
Character m_slime;
Character m_fish;
Character m_trex;
Character m_demon;
Character m_sahur;
Character m_dragon;
Character e_empty;

const char *squid[] =
{
    "\t\t                                                          ",//16
    "\t\t                                                          ",//17
    "\t\t                                                          ",//18
    "\t\t                                                          ",//19
    "\t\t                                                          ",//15
    "\t\t     +--------------------------------------------------+ ",//12
    "\t\t     |Hope is dust. Let me show you how easily it fades.| ",//13
    "\t\t     +--------------------------------------------------+ ",//14
    "\t\t    .---.                                                 ",//1
    "\t\t   /     \\                                               ",//2
    "\t\t  |  .-.  |                                               ",//3
    "\t\t  | (o o) |                                               ",//4
    "\t\t  |  '-'  |                                               ",//5
    "\t\t   \\  .  /                                               ",//6
    "\t\t   '--'--.                                                ",//7
    "\t\t  /  /\\   \\                                             ",//8
    "\t\t /  /  \\   \\                                            ",//9
    "\t\t|  |    |  |                                              ",//10
    "\t\t \\|     |/                                               "//11
};

const char* dino[] =
{
    "\t\t",//19
    "\t\t",//18
    "\t\t",//17
    "\t\t",//16
    "\t\t",//15
    "\t\t",//14
    "\t\t",//13
    "\t\t",//12
    "\t\t",//11
    "\t\t",//10
    "\t\t  ___        +---------------------------------------------+   ",//1
    "\t\t (_  \\       |The sun left us. Your spark will vanish next.|  ",//2
    "\t\t   \\  \\      +---------------------------------------------+ ",//4
    "\t\t    \\  \\_/\\/\\/\\/\\_                                       ",//3
    "\t\t     \\            |_                                          ",//5
    "\t\t      \\             |_                                        ",//6
    "\t\t       |              |_                                       ",//7
    "\t\t       | |)   (| |)     \\                                     ",//8
    "\t\t       |_|-----|_|'--\\___\\                                   ",//9
};

const char* slime[] =
{
    "\t\t",//19
    "\t\t",//18
    "\t\t",//17
    "\t\t",//16
    "\t\t",//15
    "\t\t",//14
    "\t\t",//13
    "\t\t",//12
    "\t\t     +-------------------------------------------------------+ ",//11
    "\t\t     | I've seen countless lights die. Yours will join them. | ",//10
    "\t\t     +-------------------------------------------------------+ ",//9
    "\t\t                                                               ",//8
    "\t\t        ********                                               ",//1
    "\t\t    **            **                                           ",//2
    "\t\t  **   ==    ==     **                                         ",//3
    "\t\t **                  **                                        ",//4
    "\t\t**      vvvvvv        **                                       ",//5
    "\t\t**                    **                                       ",//6
    "\t\t************************                                       ",//7
};

const char* fish[] =
{
    "\t\t",//20
    "\t\t",//19
    "\t\t",//18
    "\t\t",//17
    "\t\t",//16
    "\t\t",//15
    "\t\t",//14
    "\t\t           +-----------------------------------------+",//10
    "\t\t           |I failed the dawn... and now so will you.|",//11
    "\t\t           +-----------------------------------------+",//12
    "\t\t       .   ,  ,    .                                  ",//1
    "\t\t       )\\_/|_/|_  /                                  ",//2
    "\t\t    .-'        /_/(                                   ",//3
    "\t\t   '  .-'`'-.   /_(                                   ",//4
    "\t\t  /  (    o  ) /___(                                  ",//5
    "\t\t /u   '-._.-'  \\ _(/                                 ",//6
    "\t\t^--------^-^-)  ) \\_     /                           ",//7
    "\t\t\\ _________         '-._.)\\                         ",//8
    "\t\t (,(,(,(_______)_____..---'                           "//9
};

const char* trex[] =
{
    "\t\t",//19
    "\t\t",//18
    "\t\t",//17
    "\t\t",//16
    "\t\t  ********    +-------------------------------------------+",//1
    "\t\t*        **   | Every spark I touch dies. Yours will too. |",//2
    "\t\t*      O **   +-------------------------------------------+",//3
    "\t\t*        **                                                ",//4
    "\t\t ******  **      *                                         ",//5
    "\t\t  *****  ***     *                                         ",//6
    "\t\t    ***    ***  **                                         ",//7
    "\t\t      *      *****                                         ",//8
    "\t\t     ***         *                                         ",//9
    "\t\t     * *         *                                         ",//10
    "\t\t       *        *                                          ",//11
    "\t\t        * ***  *                                           ",//12
    "\t\t        ********                                           ",//13
    "\t\t        *** ****                                           ",//14
    "\t\t       ****  ***                                           "//15
};
const char* demon[] =
{
    "\t\t",//19
    "\t\t",//18
    "\t\t",//17
    "\t\t",//16
    "\t\t",//15
    "\t\t",//14
    "\t\t        +---------------------------------------------------+",//13
    "\t\t        | Stone remembers despair. You’re nothing before me.|",//12
    "\t\t        +---------------------------------------------------+",//11
    "\t\t   /\\__         __/\\                                       ", // 1
    "\t\t  /`    \\     /    `\\                                      ", // 2
    "\t\t===      \\___/      ===                                     ",   // 3
    "\t\t |  O    _   _    O  |                                       ",   // 4
    "\t\t \\      (     )      /                                      ",  // 5
    "\t\t /|      V---V      |\\                                      ",  // 6
    "\t\t/ |      |   |      | \\                                     ",  // 7
    "\t\t  |______|___|______|                                        ",   // 8
    "\t\t   |    |     |    |                                         ",   // 9
    "\t\t  (vvvvvv)   (vvvvvv)                                        "    // 10
};

const char *dragon[] =
{
    "",//
    "",//
    "",//
    "  +-------------------------------------------------------------+          ",//1
    "  | Your journey ends here.                                     |          ",//2
    "  | I've watched you crawl through shadows and cling to hope... |          ",//3
    "  | but this is where it finally breaks!                        |          ",//4
    "  +-------------------------------------------------------------+          ",//5
    "     |  (  \\ ( \\                                    _____                  ",//6
    "    \\ \\  `  `   )              ___                 / _   \\                 ",//7
    " (_`   \\+   . x  ( .          /   \\____-----------/ (o)   \\_               ",//8
    "- .               \\+  ;      (  O                           \\____          " ,//9
    "                         )    \\_____________  `              \\  /          ",//10
    "(__               +- .( -'.-  _  VVVVVVV VV V\\                \\/           ",//11
    "(_____           ._._: <_  _  (--  _AAAAAAA__A_/              |            ",//12
    "  .   /./.+-  . .- /  +  .     \\______________//_              \\_______    ",//13
    "  (__' /x  / x _/ (                              \\___'          \\     /    ",//14
    " , x  ( '  . / .                                     |           \\   /     ",//15
    "    / /                                              /             \\/      "//16
};

const char* sahur[] =
{
    "\t\t",//19
    "\t\t        AAAAAAAAAAAAA     +-----------------------+",//1
    "\t\t       |  --     --  |    | TUNG TUNG TUNG SAHUR! |",//2
    "\t\t       |   8     8   |    +-----------------------+",//3
    "\t\t       |  808   808  |                             ",//4
    "\t\t       \\   8  |  8   /                            ", //5
    "\t\t    ::: |     |     |:::                           ",//6
    "\t\t    H   |    ===    |  H                           ",//7
    "\t\t    H   |           |  H                           ",//8
    "\t\t    H   |           |  H                           ",//9
    "\t\t    H   |           |  H                           ",//10
    "\t\t    H   |           |  H                           ",//11
    "\t\t   (H)  |           | (H)                          ",//12
    "\t\t   !+!  |           |                              ",//13
    "\t\t   !+!  vvvvvvvvvvvvv                              ",//14
    "\t\t   !+!     ||   ||                                 ",//15
    "\t\t   !+!     ||   ||                                 ",//16
    "\t\t   !+!     ||   ||                                 ",//17
    "\t\t   !=!  #####   #####                              "//18
};


const char* swordsman[] =
{
    "                            ",//4
    "                            ",//4
    "                            ",//5
    "                            ",//6
    "                            ",//7
    "                            ",//8
    "  A                         ", //9
    " T^T                        ", //10
    " T T     ^^^^^^^^^          ", //11
    " T T     | __ __ |          ", //12
    " T T    H|  U  U |H         ", //13
    " T T     |_______|          ", //14
    "#####    ===   ===          ", //15
    " (H)>>>> II     II<<o       ", //16
    "  H      II     II   V      ", //17
    "  H      II=====II   V      ", //18
    "         /  / \\  \\  (O)     ",//19
    "        /  /   \\  \\         ",//20
    "      <wwwww) (wwwww>       "//21
    };

const char* sorcerer[] =
{
    "                            ",//4
    "                            ",//4
    "                            ",//5
    "                            ",//6
    "            @               ", // 7
    "           /o\\              ", // 8
    "          /o*o\\             ", // 9
    "         /  o  \\            ", //10
    "      <<<--------->>>       ", // 11
    "  O     | __?__ |           ", // 12
    " O*O   q|  y  y |p          ", // 13
    "  O     |_______|           ", // 14
    "#####   ===   ===           ", // 15
    " (H)>>>>II     II<<o        ", // 16
    "  H     II     II  V        ", // 19
    "  H     II=====II  V        ", // 18
    "  H     /  / \\  \\ (O)       ", // 19
    "  H    /  /   \\  \\          ", // 20
    "  H  <<<<<)   (>>>>>        "  // 21
};

const char* archer[] =
{
    "                            ",//3
    "                            ",//4
    "                            ",//5
    "                            ",//6
    "                            ",//7
    "        ***                 ",//8
    "       ccccc                ",//9
    "      ccccccc               ",//10
    "     HHHHHHHHHH    |))       ",//11
    "   HH|\\__ __/|HH   |))      ",//12
    "   Hq|  $  $  |pH  | ))     ",//13
    "   HH|________|HH  |  ))    ",//14
    "     ===   ===     |    ))  ",//15
    " o>> II     II<<<<<<(|))))  ",//16
    " V   II     II     |    ))  ",//17
    " V   II=====II     |   ))   ",//18
    "(O)  /  / \\  \\     |  ))    ",//19
    "    /  /   \\  \\    | ))     ",//20
    " <XXXXX)  (XXXXX>  |))      "//21
};

const char* empty[] =
{
    " ",//1
    " ",//2
    " ",//3
    " ",//4
    " ",//5
    " ",//6
    " ",//7
    " ",//8
    " ",//9
    " ",//10
    " ",//11
    " ",//12
    " ",//13
    " ",//14
    " ",//15
    " ",//16
    " ",//17
    " ",//18
    " ",//19

};

void CharacterData()
{
    e_empty.art = empty;
    c_swordsman.art = swordsman;
    c_sorcerer.art = sorcerer;
    c_archer.art = archer;
    m_squid.art = squid;
    m_dino.art = dino;
    m_slime.art = slime;
    m_fish.art = fish;
    m_demon.art = demon;
    m_trex.art = trex;
    m_sahur.art = sahur;
    m_dragon.art = dragon;
}
void printCharacter(Character* p, Character* m)
{

    for(int line = 0; line < 19; line++)
    {

            printf("%s", p->art[line]);
            printf("               ");
            printf("%s", m->art[line]);

            printf("\n");
    }
        printf("\n");
}

void Monster(int currentTier,Character *player,int randomMonster)
{
    //random boss
        if(currentTier == 1)
        {
            if(randomMonster == 2)      printCharacter(player,&e_empty);
            else if(randomMonster == 0) printCharacter(player,&m_squid);
            else                        printCharacter(player,&m_dino);
        }
        else if(currentTier == 2)
        {
            if(randomMonster == 2)      printCharacter(player,&e_empty);
            else if(randomMonster == 0) printCharacter(player,&m_slime);
            else                   printCharacter(player,&m_fish);
        }
        else if(currentTier == 3)
        {
            if(randomMonster == 2)      printCharacter(player,&e_empty);
            else if(randomMonster == 0) printCharacter(player,&m_demon);
            else                   printCharacter(player,&m_trex);
        }
        else
        {
            if(randomMonster == 2)      printCharacter(player,&e_empty);
            else if(randomMonster == 0)printCharacter(player,&m_dragon);
            else                  printCharacter(player,&m_sahur);

        }
}

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

void GameScreen(int currentTier,int currentBossHP,int currentBossMaxHP,int playerHP, int playerMaxHP,int score,int shield,int randomMonster,char *word,Character *player,struct Flashcard *options)
{
    int line,bars;
    int i,h;

    system("cls");

    printf("===================================================================================================================\n");

    if (currentTier == 4) printf("%40s",">> FINAL BOSS << ");
    else printf("%40s %d / 4     ","PHASE", currentTier);

    printf("|      SCORE: %d\n", score);
    printf("===================================================================================================================\n");

    printf("%18s","YOU: ");
    for(h=0; h < playerMaxHP; h++)
    {
        if(h < playerHP) printf("O");
        else printf("X");
    }
    for(h=0; h<shield; h++)
    {
        printf("[]");
    }
    printf("%58s","BOSS: ");
    if (currentBossHP > 10)
    {
        bars = 10;
    }
    else
    {
        bars = currentBossHP;
    }
    for(h=0; h<bars; h++)
    {
        if(h<bars) printf("#");
        else printf(" ");
    }
    printf(" [%d/%d]   ", currentBossHP, currentBossMaxHP);

    printf("\n");

    Monster(currentTier,player,randomMonster);

    printf("-------------------------------------------------------------------------------------------------------------------\n\n");

    if(word != NULL)
    {
        printf("\t\t\t\tQuestion: [ %s ]\n\n", word);
        for(int i=0; i<4; i++)
        {
            printf("\t\t\t\t     [%d] %s\n", i+1, options[i].definition);
        }
        printf("\n\t\t\t\t     [X] Exit Game\n");
    }
    printf("\n");
}

void EventScene(int currentTier,int currentBossHP,int currentBossMaxHP,int playerHP, int playerMaxHP,int score,int shield,int randomMonster,char *message,char *reward,Character *player)
{
    system("cls");
    GameScreen(currentTier,currentBossHP,currentBossMaxHP,playerHP,playerMaxHP,score,shield,2,NULL,player,NULL);
    printf("\t\t\t\t%s\n\n", message);
    printf("\t\t\t\t%s\n\n", reward);
    printf("\t\t\t\tEnter any key to continue...");
    _getch();
}

void RandomEvent(int *playerHP, int playerMaxHP, int *score, int *shield, int currentTier, int currentBossHP, int currentBossMaxHP,int randomMonster,Character *player)
{
    char message[100]= "Nothing here";
    char reward[100] = "Nothing here";

    int event = rand() % 2;
    int item = rand() % 3;

    if(event == 0)
    {
        switch(item)
        {
        case 0:
            strcpy(message,"A soft glow circles you briefly. You feel your strength steady.");
            break;
        case 1:
            strcpy(message,"A pale orb bursts softly above you. A calm warmth remains.");
            break;
        case 2:
            strcpy(message,"A glowing mushroom dissolves into your palm. Energy stirs through you.");
            break;
        default:
            strcpy("Error",message);
            break;
        }
        strcpy(reward,"Reward: +1 HP");
        if(*playerHP < playerMaxHP) (*playerHP)++;
        else strcat(reward," >>Your HP is full");
    }

    if(event == 1)
    {
        switch(item)
        {
        case 0:
            strcpy(message,"A warm ember drifts into your hand. Your vision sharpens.");
            break;
        case 1:
            strcpy(message,"Dew glimmers at your feet. You drink, feeling lighter.");
            break;
        case 2:
            strcpy(message,"A molten shard drifts into your hand. You drink, Power pulses briefly.");
            break;
        default:
            strcpy("Error",message);
            break;
        }

        strcpy(reward,"Reward: +1 Shield");
        if(*shield < 2) (*shield)++;
        else strcpy(message,"Your Shield is full");
    }

    EventScene(currentTier,currentBossHP,currentBossMaxHP,*playerHP,playerMaxHP,*score,*shield,randomMonster,message,reward,player);
}

void PlayRPG(struct Flashcard *deck, int count)
{

    CharacterData();

    int choice;
    int randomMonster = rand() % 2;
    Character* player;

    //start_story();



    while(1)
    {
        system("cls");
        printf("==============================================================================================\n");
        printf("%55s\n","Choose your character");
        printf("==============================================================================================\n\n");
        printf("   [1] Swordsman\n");
        printf("       :Trained with Luminsteel, the last blade forged from captured sunlight.\n");
        printf("        Your village fell to shadows, leaving only you to carry its hope.\n");
        printf("        You are the final spark of Emberfall - the promise of an entire village's dawn.\n");
        printf("\n");
        printf("   [2] Sorcerer\n");
        printf("       :You hold ancient runes pulsing with starlight, the world's last knowledge of light.\n");
        printf("        Chosen by the Arcana, your steps alone can awaken the sun.\n");
        printf("        You are the one the runes have marked to bring back the first dawn.\n");
        printf("\n");
        printf("   [3] Archer\n");
        printf("       :Raised among whispering trees and arrows of Sunroot wood.\n");
        printf("        The forest entrusted its last breath to you.\n");
        printf("        You are the forest's final hope - the wind itself bends to your aim.\n");
        printf("\n");
        printf("   Select: ");
        scanf("%d",&choice);
        clearBuffer();

        if(choice == 1)
        {
            player = &c_swordsman;
            break;
        }
        else if(choice == 2)
        {
            player = &c_sorcerer;
            break;
        }
        else if(choice == 3)
        {
            player = &c_archer;
            break;
        }
        else
        {
            printf("[!] Invalid Input! Please try again\n");
            Sleep(1000);
            continue;
        }
    }

    printf("Entering game");
    Sleep(100);
    printf(".");
    Sleep(100);
    printf(".");
    Sleep(100);
    printf(".");
    Sleep(500);

    system("cls");

    int tierHP[5];
    CalculateBossHP(count,tierHP);
    int currentTier = 1;

    int currentBossMaxHP = tierHP[1];
    int currentBossHP = tierHP[1];
    int playerHP = count/3;
    int playerMaxHP = count/3;

    int remaining = count;
    int score = 0;
    int shield = 0;

    int correctIdx;
    int currentIdx;

    int selected = -1;
    char key;
    char exit;

    struct Flashcard options[4];


    GameScreen(currentTier, currentBossHP, currentBossMaxHP, playerHP, playerMaxHP, score, shield, randomMonster, deck[currentIdx].word, player, options);

    while (remaining > 0 && playerHP > 0)
    {

        system("cls");
        currentIdx = rand() % remaining;
        GenerateOptions(deck, count, currentIdx, options, &correctIdx);
        GameScreen(currentTier,currentBossHP,currentBossMaxHP,playerHP,playerMaxHP,score,shield,randomMonster,deck[currentIdx].word,player,options);


        while(1)
            {
                fflush(stdin);

                printf("\t\t\t\tAttack (1-4): ");
                key = _getch();
                key = tolower(key);
                if(key >= '1' && key <= '4')
                {
                    selected = key - '1';
                    break;
                }
                else if(key == 'x')
                {
                    printf("\nDo you want to exit game?(y/n): ");
                    exit = _getch();
                    exit = tolower(exit);
                    if(exit == 'y') return;
                    GameScreen(currentTier,currentBossHP,currentBossMaxHP,playerHP,playerMaxHP,score,shield,randomMonster,deck[currentIdx].word,player,options);
                }
                else
                {
                    printf("\n\t\t\t[!] Invalid input. Please try again");
                    Sleep(1200);
                    GameScreen(currentTier,currentBossHP,currentBossMaxHP,playerHP,playerMaxHP,score,shield,randomMonster,deck[currentIdx].word,player,options);
                }
            }

        if (selected == correctIdx)
        {
            printf(" >>> CRITICAL HIT! <<<");
            score++;
            currentBossHP--;
            remaining--;
            SwapCards(&deck[currentIdx], &deck[remaining]);

            if (currentBossHP <= 0 && remaining > 0)
            {
                printf("\n\n\t\t\t\t *** LEVEL CLEARED! BOSS EVOLVED! ***");
                Sleep(1200);
                RandomEvent(&playerHP,playerMaxHP,&score,&shield,currentTier,currentBossHP,currentBossMaxHP,randomMonster,player);

                currentTier++;
                randomMonster = rand() % 2;
                currentBossMaxHP = tierHP[currentTier];
                currentBossHP = currentBossMaxHP;
                continue;
            }
        }
        else
        {
            printf(" >>> MISS! You took damage! <<<");
            printf("\n\n\t\t\t\tCorrect: [%d] %s", correctIdx+1, deck[currentIdx].definition);

            if(shield > 0)
            {
                printf("\n\n\t\t\t\tYour shield is broken");
                shield--;
            }
            else playerHP--;

            Sleep(1200);
        }

        Sleep(1200);
    }

    //Result

    system("cls");

    if(playerHP > 0)
    {
        final_cut();

        printf("\t                                       VICTORY!\n");
        printf("\t                      ==============================================\n");
        printf("\t                                You defeated all monsters!\n");
        printf("\t                      ==============================================\n");
        printf("\n");
    }
    else
    {
        final_loss();
        printf("\t                                      GAME OVER!\n");
        printf("\t                      ==============================================\n");
        printf("\t                               You fall into the darkness...\n");
        printf("\t                      ==============================================\n");

    }
    printf("\t                              +--------------------------+\n");
    printf("\t                              |    FINAL SCORE: %2d / %2d  |\n",score,count);
    printf("\t                              +--------------------------+ \n");

    printf("\n");
    printf("\t                              Press any key to return...");
    _getch();
    return;

}

void StartGame(char *setName)
{
    struct Flashcard deck[100];
    int totalCards;

    system("cls");

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
    char choice;
    int lineNum;
    char setName[100];
    char confirm;

    do
    {
        system("cls");
        printf("[1] Start\n");
        printf("[2] Learn\n");
        printf("[3] Manage\n");
        printf("[X] Close Program\n");

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
                            StartGame(setName);
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
                        printf("[Error]: Set number %d does not exist\n",lineNum);
                        Sleep(1200);
                    }
                    break;
                }

            case '2': printf("Learn"); break;

            case '3': RunSetMenu(); break;

            case 'x': return 0;

            default :
                printf("\n Invalid input! Please try again.\n");
                Sleep(1000);
        }
    }while(choice != 'x');
    return 0;
}
