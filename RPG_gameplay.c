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
//Character
typedef struct {
    char name[20];
    int lines;
    int width;
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

Character m_dragon;

const char *squid[] =
{
    "    .---.    ",//1
    "   /     \\    ",//2
    "  |  .-.  |  ",//3
    "  | (o o) |  ",//4
    "  |  '-'  |  ",//5
    "   \\  .  /  ",//6
    "   '--'--.   ",//7
    "  /  /\\   \\  ",//8
    " /  /  \\   \\  ",//9
    "|  |    |  |  ",//10
    " \\|     |/     ",//11
};

const char* dino[] =
{
    "  __                        ",//1
    " (_ \\                     ",//2
    "   \\ \\                   ",//4
    "    \\ \\_/\\/\\/\\/\\_    ",//3
    "     \\           |_       ",//5
    "      \\            |_     ",//6
    "       |             |_    ",//7
    "       | |)  (| |)     \\  ",//8
    "       |_|----|_|'--\\___\\",//9
};

const char* slime[] =
{
    "        ********        ",//1
    "    **            **    ",//2
    "  **   #      #     **  ",//3
    " **                  ** ",//4
    "**      vvvvvv        **",//5
    "**                    **",//6
    "************************",//7
};

const char* fish[] =
{
    "       .   ,  ,    .         ",//1
    "       )\\_/|_/|_  /         ",//2
    "    .-'        /_/(          ",//3
    "   '  .-'`'-.   /_(          ",//4
    "  /  (    o  ) /___(         ",//5
    " /u   '-._.-'  \\ _(/        ",//6
    "^--------^-^-)  ) \\_     /  ",//7
    "\\ _________         '-._.)\\",//8
    " (,(,(,(_______)_____..---'  "//9
};

const char* trex[] =
{
    "  ********          ",//1
    " *       **         ",//2
    " *     * **         ",//3
    " *       **         ",//4
    " ******  **      *  ",//5
    "  *****  ***     *  ",//6
    "    ***    ***  **  ",//7
    "      *      *****  ",//8
    "     ***         *  ",//9
    "     * *         *  ",//10
    "       *        *   ",//11
    "        * ***  *    ",//12
    "        ********    ",//13
    "        *** ****    ",//14
    "       ****  ***    "//15
};
const char* demon[] =
{
    "   /\\__         __/\\   ", // 1
    "  /`    \\     /    `\\  ", // 2
    "===      \\___/      === ",   // 3
    " |  O    _   _    O  |   ",   // 4
    " \\      (     )      /  ",  // 5
    " /|      V---V      |\\  ",  // 6
    "/ |      |   |      | \\ ",  // 7
    "  |______|___|______|    ",   // 8
    "   |    |     |    |     ",   // 9
    "  (vvvvvv)   (vvvvvv)    "    // 10
};

const char *dragon[] =
{
    "                        _____                 ",//1
    "   ___                 / _   \\              ",//2
    "  /   \\____-----------/ (o)   \\_           ",//3
    " (  O   )                        \\____      ",//4
    " \\_____________                   \\  /     ",//5
    "   VVVVVVV VV V\\                   \\/      ",//6
    "  (AAAAAAAAAAA__A_/                |          ",//7
    "   \\______________//_              \\_______",//8
    "                     \\___           \\     /",//9
    "                         |           \\   /  ",//10
    "                        /             \\/    "//11
};

const char* swordsman[] =
{
    "  A                       ", //1
    " T^T                      ", //2
    " T T     ^^^^^^^^^        ", //3
    " T T     | __ __ |        ", //4
    " T T    H|  U  U |H       ", //5
    " T T     |_______|        ", //6
    "#####    ===   ===        ", //7
    " (H)>>>> II     II<<o     ", //8
    "  H      II     II   V    ", //9
    "  H      II=====II   V    ", //10
    "         /  / \\  \\  (O)   ",//11
    "        /  /   \\  \\       ",//12
    "      <wwwww) (wwwww>     "//13
    };

const char* sorcerer[] =
{
    "            @            ", // 1
    "           /o\\            ", // 2
    "          /o*o\\           ", // 3
    "         /  o  \\          ", // 4
    "      <<<--------->>>    ", // 5
    " O      | __?__ |        ", // 6
    " O*O   q|  y  y |p       ", // 7
    "  O     |_______|        ", // 8
    "#####   ===   ===        ", // 9
    " (H)>>>>II     II<<o     ", // 10
    "  H     II     II  V     ", // 11
    "  H     II=====II  V     ", // 12
    "  H     /  / \\  \\ (O)    ", // 13
    "  H    /  /   \\  \\       ", // 14
    "  H  <<<<<)   (>>>>>     "  // 15
};

const char* archer[] =
{
    "        ***                 ",//1
    "       ccccc                ",//2
    "      ccccccc               ",//3
    "     HHHHHHHHHH             ",//4
    "   HH|\\__ __/|HH   |))      ",//5
    "   Hq|  $  $  |pH  | ))     ",//6
    "   HH\\    3  /HH   |  ))    ",//7
    "   HH |_____| HH   |   ))   ",//8
    "     ===   ===     |    ))  ",//9
    " o>> II     II<<<<<<(|))))  ",//10
    " V   II     II     |    ))  ",//11
    " V   II=====II     |   ))   ",//12
    "(O)  /  / \\  \\     |  ))    ",//13
    "    /  /   \\  \\    | ))     ",//14
    " <XXXXX)  (XXXXX>  |))      "//15
};

void CharacterData()
{
    strcpy(c_swordsman.name,"Swordsman");
    c_swordsman.lines = 13;
    c_swordsman.width = 26;
    c_swordsman.art = swordsman;

    strcpy(c_sorcerer.name,"Sorcerer");
    c_sorcerer.lines = 15;
    c_sorcerer.width = 26;
    c_sorcerer.art = sorcerer;

    strcpy(c_archer.name,"Archer");
    c_archer.lines = 15;
    c_archer.width = 28;
    c_archer.art = archer;

    strcpy(m_squid.name,"Squid");
    m_squid.lines = 11;
    m_squid.width = 14;
    m_squid.art = squid;

    strcpy(m_dino.name,"Dino");
    m_dino.lines = 9;
    m_dino.width = 27;
    m_dino.art = dino;

    strcpy(m_slime.name,"Slime");
    m_slime.lines = 7;
    m_slime.width = 24;
    m_slime.art = slime;

    strcpy(m_fish.name,"Fish");
    m_fish.lines = 9;
    m_fish.width = 29;
    m_fish.art = fish;

    strcpy(m_demon.name,"Demon");
    m_demon.lines = 10;
    m_demon.width = 30;
    m_demon.art = demon;

    strcpy(m_trex.name,"T-Rex");
    m_trex.lines = 15;
    m_trex.width = 20;
    m_trex.art = trex;

    strcpy(m_dragon.name,"Dragon");
    m_dragon.lines = 11;
    m_dragon.width = 45;
    m_dragon.art = dragon;
}

void printCharacter(Character* p, Character* m)
{

    int lines,maxLines;
    int pStart,mStart;

    if (p->lines > m->lines)
    {
        maxLines = p->lines;
    }
    else
    {
        maxLines = m->lines;
    }

    for(int line = 0; line < maxLines; line++) {

        pStart = maxLines - p->lines;

        if(line >= pStart)
        {
            printf(" %s", p->art[line - pStart]);
        }
        else
        {
            printf(" %*s", p->width, "");
        }

        printf("                 ");

        mStart = maxLines - m->lines;

        if(line >= mStart)
        {
            printf("%s", m->art[line - mStart]);
        }
        printf("\n");
    }
}

void Monster(int currentTier,Character *player,int randomMonster)
{
    //random boss
        if(currentTier == 1)
        {
            if(randomMonster == 0) printCharacter(player,&m_squid);
            else                   printCharacter(player,&m_dino);
        }
        else if(currentTier == 2)
        {
            if(randomMonster == 0) printCharacter(player,&m_slime);
            else                   printCharacter(player,&m_fish);
        }
        else if(currentTier == 3)
        {
            if(randomMonster == 0) printCharacter(player,&m_demon);
            else                   printCharacter(player,&m_trex);
        }
        else
        {
            printCharacter(player,&m_dragon);
        }
}
void GameScreen(int currentTier,int currentBossHP,int currentBossMaxHP,int playerHP, int playerMaxHP,int score,int shield,int randomMonster,char *word,Character *player,struct Flashcard *options)
{
    int line,bars;
    int i,h;

    system("cls");

    printf("==========================================================================================\n");

    if (currentTier == 4) printf("%25s",">> FINAL BOSS << ");
    else printf("%25s %d / 4     ","PHASE", currentTier);

    printf("|      SCORE: %d\n", score);
    printf("==========================================================================================\n");

    printf("%15s","YOU: ");
    for(h=0; h < playerMaxHP; h++)
    {
        if(h < playerHP) printf("O");
        else printf("X");
    }
    for(h=0; h<shield; h++)
    {
        printf("[]");
    }
    printf("%30s","BOSS: ");
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

    printf("------------------------------------------------------------------------------------------\n");

    if(word != NULL)
    {
        printf(" Question: [ %s ]\n", word);
        for(int i=0; i<4; i++)
        {
            printf(" [%d] %s\n", i+1, options[i].definition);
        }
    }
}

void EventScene(int currentTier,int currentBossHP,int currentBossMaxHP,int playerHP, int playerMaxHP,int score,int shield,int randomMonster,char *message,char *reward,Character *player)
{
    system("cls");
    GameScreen(currentTier,currentBossHP,currentBossMaxHP,playerHP,playerMaxHP,score,shield,randomMonster,NULL,player,NULL);
    printf("      %s\n\n", message);
    printf("      %s\n\n", reward);
    printf("Enter any key to continue...");
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
        else strcat(reward," Your HP is full");
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

    if(count < 4)
    {
        printf("\n [Error] Not enough cards! Need at least 4 cards.\n");
        Sleep(2000);
        return;
    }

    CharacterData();

    int choice;
    int randomMonster = rand() % 2;
    Character* player;

    while(1)
    {
        system("cls");

        printf("==============================================================================================\n");
        printf("%55s\n","Choose your character");
        printf("==============================================================================================\n");
        printf("[1] Swordsman\n");
        printf("    :Trained with Luminsteel, the last blade forged from captured sunlight.\n");
        printf("     Your village fell to shadows, leaving only you to carry its hope.\n");
        printf("     You are the final spark of Emberfall - the promise of an entire village's dawn.\n");
        printf("\n");
        printf("[2] Sorcerer\n");
        printf("    :You hold ancient runes pulsing with starlight, the world's last knowledge of light.\n");
        printf("     Chosen by the Arcana, your steps alone can awaken the sun.\n");
        printf("     You are the one the runes have marked to bring back the first dawn.\n");
        printf("\n");
        printf("[3] Archer\n");
        printf("    :Raised among whispering trees and arrows of Sunroot wood.\n");
        printf("     The forest entrusted its last breath to you.\n");
        printf("     You are the forest's final hope - the wind itself bends to your aim.\n");
        printf("\n");
        printf("Select: ");
        scanf("%d", &choice);

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
        else printf("[!] Invalid Input!\n");
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
    int shield = 0;

    struct Flashcard options[4];
    int correctIdx;
    int currentIdx;

    int selected = -1;
    char key;

    while (remaining > 0 && playerHP > 0)
    {
        currentIdx = rand() % remaining;
        GenerateOptions(deck, count, currentIdx, options, &correctIdx);
        GameScreen(currentTier,currentBossHP,currentBossMaxHP,playerHP,playerMaxHP,score,shield,randomMonster,deck[currentIdx].word,player,options);


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
                    printf("[Error] Invalid input.");
                    Sleep(1500);
                    GameScreen(currentTier,currentBossHP,currentBossMaxHP,playerHP,playerMaxHP,score,shield,randomMonster,deck[currentIdx].word,player,options);
                }
            }

        if (selected == correctIdx)
        {
            printf("\n\n >>> CRITICAL HIT! <<<\n");
            score++;
            currentBossHP--;
            remaining--;
            SwapCards(&deck[currentIdx], &deck[remaining]);

            if (currentBossHP <= 0 && remaining > 0)
            {
                printf("\n *** LEVEL CLEARED! BOSS EVOLVED! ***\n");
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
            printf("\n\n >>> MISS! You took damage! <<<\n");
            printf(" Correct: [%d] %s\n", correctIdx+1, deck[currentIdx].definition);
            if(shield > 0)
            {
                printf("Your shield is broken");
                shield--;
            }

            else playerHP--;
        }

        Sleep(1200);
    }

    //Result
    system("cls");
    printf("========================================\n");
    if(playerHP > 0)
    {
        printf("             VICTORY! \n");
        printf("========================================\n");
        printf(" You defeated all monsters!\n");
    }
    else
    {
        printf("             GAME OVER \n");
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

