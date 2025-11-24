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

char co;
char ce = ' ';
char cn;

void repeat(char w[][100],char def[][100],int rep,char *name);
void learn();
int st=0;


void clearBuffer();
void trimNewline(char *str);
int GetLine(char *name ,char *buffer);
int AddSet();
void DelSet(char *title);
void EditSetTitle(char *old_title);
void AddCard(char *title);
void DelCard(char *word,char *title);
void CardList(char *title);
void SetList();
void CardMenu(char *title);
void RunSetMenu();

int LoadDeck(char *setName, struct Flashcard *deck);
void ShuffleDeck(struct Flashcard *deck, int count);
void GenerateOptions(struct Flashcard *deck, int count, int currentIdx, struct Flashcard *options, int *correctOptionIdx);
void SwapCards(struct Flashcard *a, struct Flashcard *b);
void readtext(char *story);

void printCharacter(const char** p, const char** m);
void Boss(int currentTier,const char** player,int randomBoss);
void CalculateBossHP(int count, int *tierHP);
void GameScreen(int currentTier,int currentBossHP,int currentBossMaxHP,int playerHP, int playerMaxHP,int score,int shield,int randomBoss,char *word,const char** player,struct Flashcard *options);
void EventScene(int currentTier,int currentBossHP,int currentBossMaxHP,int playerHP, int playerMaxHP,int score,int shield,int randomBoss,char *message,char *reward,const char** player);
void RandomEvent(int *playerHP, int playerMaxHP, int *score, int *shield, int currentTier, int currentBossHP, int currentBossMaxHP,int randomBoss,const char** player);
void PlayRPG(struct Flashcard *deck, int count);

void StartGame(char *setName);
void GameTitle();

//Character
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
    "\t\t        | Stone remembers despair. You're nothing before me.|",//12
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
    "   HH|\\__ __/|HH   | ))     ",//12
    "   Hq|  $  $  |pH  |  ))    ",//13
    "   HH|________|HH  |   ))   ",//14
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
    "                            ",//1
    "                            ",//2
    "                            ",//3
    "                            ",//4
    "                            ",//5
    "                            ",//6
    "                            ",//7
    "                            ",//8
    "                            ",//9
    "                            ",//10
    "                            ",//11
    "                            ",//12
    "                            ",//13
    "                            ",//14
    "                            ",//15
    "                            ",//16
    "                            ",//17
    "                            ",//18
    "                            ",//19

};


int main()
{
    int lineNum;
    char choice;
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
                    if(GetLine("set_list",setName) == 1)
                    {
                        printf("\t\t\t>> %s is selected, You want to continue?(y/n): ",setName);
                        confirm = _getch();
                        printf("%c\n",confirm);
                        if(confirm == 'y')
                        {
                            StartGame(setName);
                            break;
                        }
                        else
                        {
                            printf("\t\t\t> Canceled <");
                            fflush(stdout);
                            Sleep(1000);
                        }
                    }
                }
                break;

            case '2': learn(); break;

            case '3': RunSetMenu(); break;

            case 'x': return 0;

            default :
                printf("\n [!] Invalid input. Please try again.\n");
                Sleep(1000);
        }
    }while(choice != 'x');
    return 0;
}

//Game Title
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
        printf("       ###### ###### ##   #####       ###       ##    ## ###### ##     ##    ######     ###   ##     ## ##    ##\n");
        printf("         ##     ##   ##  ##         ##   ##     ###   ## ##     ##  #  ##    ##    #  ##   ## ##  #  ## ###   ##\n");
        printf("         ##     ##        #####     #######     ## ## ## ###### ## ### ##    ##     # ####### ## ### ## ## ## ##\n");
        printf("         ##     ##            ##    ##   ##     ##   ### ##     ###   ###    ##    #  ##   ## ###   ### ##   ###\n");
        printf("       ######   ##        #####     ##   ##     ##    ## ###### ##     ##    ######   ##   ## ##     ## ##    ##\n");

        printf("\n------------------------------------------------------------------------------------------------------------------------\n");
        printf("\n                                             RPG LERNING FLASHCARD GAME\n");
        printf("\n------------------------------------------------------------------------------------------------------------------------\n");
        printf("\n");
}

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

int GetLine(char *name ,char *buffer)
{
    int current_line = 1;
    int lineNum;
    char str[200];
    char file_name[100];

    while(1)
    {
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
            return 0;
        }
        else break;
    }

    sprintf(file_name,"%s.txt",name);

    FILE *fp = fopen(file_name,"r");
    if(fp == NULL)
    {
        printf("\t\t\t< File is empty >");
    }

    while(fgets(str,sizeof(str),fp) != NULL)
    {
        if(current_line == lineNum)
        {
            trimNewline(str);
            strcpy(buffer,str);

            fclose(fp);
            return 1;
        }
        current_line++;
    }

    fclose(fp);

    printf("\t\t\t[!] Card number %d not found\n",lineNum);
    Sleep(1200);
}

//file management function
int AddSet(char *setName)
{
    char file_name[100];
    char title[100];
    int MaxLen = 25;

     while(1)
    {
        fflush(stdin);
        printf("\t\t\tEnter title (max %d chars) (or enter 0 to go back): ", MaxLen);
        fgets(title,sizeof(title),stdin);
        trimNewline(title);

        if(strcmp(title, "0") == 0)
            break;

        if(strlen(title) == 0)
        {
            printf("\n\t\t\t[!] Empty input is not allowed.\n");
            Sleep(1000);
            continue;
        }
        else if(strlen(title) > MaxLen)
        {
            printf("\n\t\t\t[!] Word is too long! Maximum is %d characters.\n", MaxLen);
            Sleep(1000);
            continue;
        }
        else break;
    }

    sprintf(file_name, "%s.txt", title);

    FILE *fp = fopen(file_name, "w");
    FILE *master = fopen("set_list.txt", "a");

    if(fp == NULL || master == NULL)
    {
        printf("\t\t\t< File is empty >");
        return 0;
    }

    fprintf(master, "%s\n", title);

    fclose(fp);
    fclose(master);

    strcpy(setName,title);

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
    int MAX_LEN = 25;
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

    printf("\n\t\t\tTitle changed successfully.\n ");
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

void CardList(char *title)
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

void SetList()
{
    char str[200];
    int count = 1;
    FILE *fp = fopen("set_list.txt","r");

    if(fp == NULL)
    {
        printf("\t\t\t< File is empty >");
        //return 0;
    }

    while(fgets(str,sizeof(str),fp)!= NULL)
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
                 printf("\t\t\tEnter line number to delete(0 to cancel): ");
                 if(GetLine(title,card) == 1)
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
                    if (AddSet(setName)==1) CardMenu(setName);
                    break;

            case 'd':
                    printf("\t\t\tEnter line number to delete(0 to cancel): ");
                    if(GetLine("set_list",setName) == 1)
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
                    }
                    break;
            case 'm':
                    printf("\t\t\tEnter line number to manage(0 to cancel): ");
                    if(GetLine("set_list",setName) == 1)
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
void learn()
{
    int ch,count=0,count2=0,i=0,j,space=0,end=0,status;
    int b=0,sp,en;
    int cor;
    int maxspace = 50;
    char set_num;
    char set_name[100];
    char p[100];
    char w[100][100];
    char w_mem[100][100];
    char def[100][100];
    char def_mem[100][100];
    char origi[100];
    char card_file[100];

    FILE *c;
    FILE *a;
    while(1)
    {
        system("cls");
        printf("\t\t\t========================= LEARN =========================\n\n"); //make more beautiful interface

        SetList();

        char buf[10];

        printf("\n\t\t\tEnter number to choose the set(enter 0 to go back): ");

        fflush(stdin);
        co = _getch();
        if(co=='0') return;

        printf("%c",co);
        ch = co - '0';

        c = fopen("set_list.txt","r");


        while(!feof(c))
        {
            //fscanf(c,"%c",set_num);
            GetLine("set_list",set_name);
            if(ch==NULL)
            {
                printf("\t\t\t\t[!]No CARD SET found. Please insert card category!!/n");
                printf("\n");
                printf("\t\t\t\t[X] Back to Main Menu\n");
                printf("\t\t\t\t[Q] Quit the Program\n");

                co = _getch();
                co = tolower(co);
                if(co=='x') return;
                if(co=='q') break;
            }

            clearBuffer();

            sprintf(card_file,"%s.txt",set_name);
            a = fopen(card_file,"r");

            while (fgets(origi, sizeof(origi), a))
            {
                origi[strcspn(origi, "\n")] = '\0';

                char *word = strtok(origi, ":");
                char *defi  = strtok(NULL, ":");

                if (word != NULL)
                {
                    strcpy(w[count2], word);
                }

                if (defi != NULL)
                {
                    strcpy(def[count2], defi);
                }

                count2++;
            }

            while(1)
            {

                for(i=0; i<count2; i++)
                {
                    int mode = count % 2;  // 0 = word, 1 = def

                    if(mode==0)
                    {
                        system("cls");
                        printf("\t\t\t------------------------- %s -------------------------\n",set_name);
                        printf("\t\t\t\t    -------------------------------------------------\n");
                        printf("\t\t\t\t   |                                                 |\n"); //50 space
                        printf("\t\t\t\t   |                                                 |\n");

                        space = strlen(w[i]);
                        sp = (maxspace-space);
                        printf("\t\t\t\t");
                        printf("   |");

                        if(sp%2==0)
                        {
                            for(j=0; j<sp/2; j++) printf(" ");
                            printf("%s",w[i]);
                            for(j=0; j<sp/2; j++) printf(" "); printf("|\n");
                        }

                        else
                        {
                            for(j=0; j<sp/2; j++) printf(" ");
                            printf("%s",w[i]);
                            for(j=0; j<(sp/2)+1; j++) printf(" "); printf("|\n");
                        }

                        printf("\t\t\t\t   |                                                 |\n");
                        printf("\t\t\t\t   |                                                 |\n");
                        printf("\t\t\t\t    -------------------------------------------------\n");

                        printf("\t\t\t\t         Press ENTER to flip cards \n");
                        //en = 6;

                        do
                        {
                            fflush(stdin);
                            ce = _getch();

                        }while(ce!='\r');

                        st = 0; system("cls");
                        i--;
                        count++;
                        ce = ' ';
                    }

                    if(mode==1)
                    {
                        system("cls");
                        printf("\t\t\t------------------------- %s -------------------------\n",set_name);
                        printf("\t\t\t\t    --------------------------------------------------\n");
                        printf("\t\t\t\t   |                                                  |\n"); //50 space
                        printf("\t\t\t\t   |                                                  |\n");

                        //if(en==1) i++;

                        space = strlen(def[i]);
                        sp = (maxspace-space);
                        printf("\t\t\t\t");
                        printf("   |");

                        if(sp%2==0)
                        {
                            for(j=0; j<sp/2; j++) printf(" ");
                            printf("%s",def[i]);
                            for(j=0; j<sp/2; j++) printf(" "); printf("|\n");
                        }

                        if(sp%2==1)
                        {
                            for(j=0; j<sp/2; j++) printf(" ");
                            printf("%s",def[i]);
                            for(j=0; j<(sp/2)+1; j++) printf(" "); printf("|\n");
                        }

                        //printf("   |                 %s               |\n",w[i]);
                        printf("\t\t\t\t   |                                                  |\n");
                        printf("\t\t\t\t   |                                                  |\n");
                        printf("\t\t\t\t    --------------------------------------------------\n");

                        printf("\n");
                        printf("\t\t\t\t    [1] Pass\n");
                        printf("\t\t\t\t    [2] Still Learning\n");
                        printf("\t\t\t\t    [X] Back to Menu\n");
                        printf("\n");

                        do
                        {
                            fflush(stdin);
                            cn = _getch();
                            //printf("%c",cn);
                            cn = tolower(cn);

                        }while(cn!='1' && cn!='2' && cn!='x');

                        switch(cn)
                        {
                            case '1' :
                                count++;
                                cn = '_';
                                //en = 2;
                                //cor = 1;
                                continue;
                            case '2' :
                                strcpy(w_mem[b], w[i]);
                                strcpy(def_mem[b], def[i]);
                                //en = 2;
                                b++;
                                count++;
                                //cor = 1;
                                cn = '_';
                                continue;
                            case 'x':
                                cn = '_';
                                return;
                        }
                    }
                }
                break;
            }

            if(b!=0)
            {
                repeat(w_mem,def_mem,b,set_name);
                system("cls");
                break;
            }

            if(b==0) break;
        }//while(eof)

        system("cls");
        printf("\t\t\t------------------------- %s -------------------------\n",set_name);
        printf("\t\t\t\t   Learning End: You did it!!!!\n");
        printf("\n");
        printf("\t\t\t\t   [X] Back to Main Menu\n");
        printf("\t\t\t\t   [L] Learn New Category\n");

        fflush(stdin);
        co = _getch();
        co = tolower(co);
        if(co=='x') return;
        if(co=='l') break;

        if(status==5) return;
        //if(status==6) break;

        }
    //if(status==6) continue;
    fclose(c);
    fclose(a);
}

void repeat(char w[][100],char def[][100],int rep,char *name)
{
    int i,space,j,n,a;
    int maxspace = 50;
    int count=0;
    int l = rep;

    while(rep>0)
    {
        for(i=0; i<rep; i++)
        {
            int mode = count % 2;  // 0 = word, 1 = def

            if(mode==0)
            {
                system("cls");
                printf("\t\t\t------------------------- %s -------------------------\n",name);
                printf("\t\t\t    -------------------------------------------------\n");
                printf("\t\t\t   |                                                  |\n"); //50 space
                printf("\t\t\t   |                                                  |\n");

                space = strlen(w[i]);
                int sp = (maxspace-space);
                printf("\t\t\t");
                printf("   |");

                if(sp%2==0)
                {
                    for(j=0; j<sp/2; j++) printf(" ");
                    printf("%s",w[i]);
                    for(j=0; j<sp/2; j++) printf(" "); printf("|\n");
                }

                else
                {
                    for(j=0; j<sp/2; j++) printf(" ");
                    printf("%s",w[i]);
                    for(j=0; j<(sp/2)+1; j++) printf(" "); printf("|\n");
                }

                printf("\t\t\t\t   |                                                 |\n");
                printf("\t\t\t\t   |                                                 |\n");
                printf("\t\t\t\t    -------------------------------------------------\n");

                printf("\t\t\t\t         Press ENTER to flip cards \n");

                do
                {
                    fflush(stdin);
                    ce = _getch();

                }while(ce!='\r');

                st = 0; system("cls");
                i--;
                count++;
                ce = ' ';
            }

            if(mode==1)
            {
                system("cls");
                printf("\t\t\t------------------------- %s -------------------------\n",name);
                printf("\t\t\t\t    -------------------------------------------------\n");
                printf("\t\t\t\t   |                                                 |\n"); //50 space
                printf("\t\t\t\t   |                                                 |\n");

                        //if(en==1) i++;

                space = strlen(def[i]);
                int sp = (maxspace-space);
                printf("\t\t\t\t");
                printf("   |");

                if(sp%2==0)
                {
                    for(j=0; j<sp/2; j++) printf(" ");
                    printf("%s",def[i]);
                    for(j=0; j<sp/2; j++) printf(" "); printf("|\n");
                }

                if(sp%2==1)
                {
                    for(j=0; j<sp/2; j++) printf(" ");
                    printf("%s",def[i]);
                    for(j=0; j<(sp/2)+1; j++) printf(" "); printf("|\n");
                }

                printf("\t\t\t\t   |                                                 |\n");
                printf("\t\t\t\t   |                                                 |\n");
                printf("\t\t\t\t    -------------------------------------------------\n");

                printf("\n");
                printf("\t\t\t\t    [1] Pass\n");
                printf("\t\t\t\t    [2] Still Learning\n");
                printf("\t\t\t\t    [X] Back to Menu\n");
                printf("\n");

                do
                {
                    fflush(stdin);
                    cn = _getch();
                            //printf("%c",cn);
                    cn = tolower(cn);
                }while(cn!='1' && cn!='2' && cn!='x');

                switch(cn)
                {
                    case '1' :
                        st = 0; system("cls");
                        count++;
                        rep--;

                        for(a=i; a<l; a++)
                        {
                            strcpy(w[i],w[i+1]);
                            strcpy(def[i],def[i+1]);
                        }
                        l--;
                        cn = '_';
                        continue;

                    case '2' :
                        st = 0; system("cls");
                        n = i;
                        count++;
                        cn = '_';
                        continue;

                    case '3':
                        cn = '_';
                        return;
                }
            }
        }
    }
}

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
    //srand(time(NULL));
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

void SwapCards(struct Flashcard *a, struct Flashcard *b)
{
    struct Flashcard temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

//RPG MODE
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
        if(ch == 'NULL') break;
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
    Sleep(1200);

}

void printCharacter(const char** p, const char** m)
{

    for(int line = 0; line < 19; line++)
    {
        printf("     ");
        printf("%s", p[line]);
        printf("               ");
        printf("%s", m[line]);
        printf("\n");
    }
}

void Boss(int currentTier,const char** player,int randomBoss)
{
    const char** boss;
    //random boss

        if(randomBoss == 2) boss = empty;

        else
        {
            if(currentTier == 1)
            {
                if(randomBoss == 0) boss = squid;
                else                boss = dino;
            }


            else if(currentTier == 2)
            {
                if(randomBoss == 0) boss = slime;
                else                boss = fish;
            }
            else if(currentTier == 3)
            {
                if(randomBoss == 0) boss = demon;
                else                boss = trex;
            }
            else
            {
                if(randomBoss == 0) boss = dragon;
                else                     boss = sahur;

            }
        }


        printCharacter(player,boss);
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

void GameScreen(int currentTier,int currentBossHP,int currentBossMaxHP,int playerHP, int playerMaxHP,int score,int shield,int randomBoss,char *word,const char** player,struct Flashcard *options)
{
    int line,bars;
    int i,h;

    system("cls");

    printf("========================================================================================================================\n");
    if (currentTier == 4) printf("%55s",">> FINAL BOSS <<       ");
    else printf("%45s %d / 4      ","PHASE", currentTier);

    printf("|      SCORE: %d\n", score);
    printf("========================================================================================================================\n");

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

    Boss(currentTier,player,randomBoss);

     printf("---------------------------------------------------------------------------------------------------------------------\n");

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

void EventScene(int currentTier,int currentBossHP,int currentBossMaxHP,int playerHP, int playerMaxHP,int score,int shield,int randomBoss,char *message,char *reward,const char** player)
{
    system("cls");
    if(playerHP > 0) randomBoss = 2;
    GameScreen(currentTier,currentBossHP,currentBossMaxHP,playerHP,playerMaxHP,score,shield,randomBoss,NULL,player,NULL);
    printf("\t\t\t\t%s\n\n", message);
    printf("\t\t\t\t%s\n\n", reward);
    printf("\t\t\t\tEnter any key to continue...");
    _getch();
}

void RandomEvent(int *playerHP, int playerMaxHP, int *score, int *shield, int currentTier, int currentBossHP, int currentBossMaxHP,int randomBoss,const char** player)
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

    EventScene(currentTier,currentBossHP,currentBossMaxHP,*playerHP,playerMaxHP,*score,*shield,randomBoss,message,reward,player);
}

void PlayRPG(struct Flashcard *deck, int count)
{

    int choice;
    int randomBoss = rand() % 2;
    const char** player;


    readtext("intro_story");
    printf("\n");
    printf("\t--- Press Enter to continue ---\n");
    _getch();

    while(1)
    {
        system("cls");
        printf("========================================================================================================================\n");
        printf("%65s\n","CHOOSE YOUR CHARACTER");
        printf("========================================================================================================================\n\n");
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
            player = swordsman;
            break;
        }
        else if(choice == 2)
        {
            player = sorcerer;
            break;
        }
        else if(choice == 3)
        {
            player = archer;
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


    GameScreen(currentTier, currentBossHP, currentBossMaxHP, playerHP, playerMaxHP, score, shield, randomBoss, deck[currentIdx].word, player, options);

    while (remaining > 0 && playerHP > 0)
    {

        system("cls");
        currentIdx = rand() % remaining;
        GenerateOptions(deck, count, currentIdx, options, &correctIdx);
        GameScreen(currentTier,currentBossHP,currentBossMaxHP,playerHP,playerMaxHP,score,shield,randomBoss,deck[currentIdx].word,player,options);


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
                    printf("\n\t\t\t\tDo you want to exit game?(y/n): ");
                    exit = _getch();
                    exit = tolower(exit);
                    if(exit == 'y') return;
                    GameScreen(currentTier,currentBossHP,currentBossMaxHP,playerHP,playerMaxHP,score,shield,randomBoss,deck[currentIdx].word,player,options);
                }
                else
                {
                    printf("\n\t\t\t[!] Invalid input. Please try again");
                    Sleep(1200);
                    GameScreen(currentTier,currentBossHP,currentBossMaxHP,playerHP,playerMaxHP,score,shield,randomBoss,deck[currentIdx].word,player,options);
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
                RandomEvent(&playerHP,playerMaxHP,&score,&shield,currentTier,currentBossHP,currentBossMaxHP,randomBoss,player);

                currentTier++;
                randomBoss = rand() % 2;
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

    if(playerHP == 0)
    {
        player = empty;
        EventScene(currentTier,currentBossHP,currentBossMaxHP,playerHP,playerMaxHP,score,shield,randomBoss,"Out of HP!","The light has faded...",player);
    }

    //Result

    system("cls");

    if(playerHP > 0)
    {
        readtext("win_story");

        printf("\t                                       VICTORY!\n");
        printf("\t                      ==============================================\n");
        printf("\t                                You defeated all monsters!\n");
        printf("\t                      ==============================================\n");
        printf("\n");
    }
    else
    {
        readtext("defeat_story");
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
        printf("\n[!] No cards found!\n");
        Sleep(2000);
        return;
    }
    else if(totalCards < 4)
    {
        printf("[!] Must have at least 4 card in the set!\n");
        Sleep(2000);
        return;
    }

    ShuffleDeck(deck,totalCards);
    PlayRPG(deck,totalCards);
}

