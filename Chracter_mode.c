#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct {
    char name[20];
    int lines;
    int width;
    const char** art;
} Character;

const char* slime[] =
{
        "          **********          ", //1
        "       **------------**       ", //2
        "    **-----#------#-----**    ", //3
        "  ***------#------#------***  ", //4
        " **------------------------** ", //5
        "***---------vvvvvv---------***", //6
        "**--------------------------**", //7
        "******************************"  //8
    };
const char* demon[] = {
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
    "            @              ", // 1
    "           /o\\             ", // 2
    "          /o*o\\            ", // 3
    "         /  o  \\           ", // 4
    "      <<<--------->>>     ", // 5
    " O      | __?__ |         ", // 6
    " O*O   q|  y  y |p        ", // 7
    "  O     |_______|         ", // 8
    "#####   ===   ===         ", // 9
    " (H)>>>>II     II<<o      ", // 10
    "  H     II     II  V      ", // 11
    "  H     II=====II  V      ", // 12
    "  H     /  / \\  \\ (O)     ", // 13
    "  H    /  /   \\  \\        ", // 14
    "  H  <<<<<)   (>>>>>      "  // 15
}; // 15 บรรทัด

Character c_swordsman = {"Swordsman", 13, 26, swordsman};
Character c_sorcerer  = {"Sorcerer", 15, 25, sorcerer};
Character m_slime = { "Slime", 8, 30, slime};
Character m_demon = { "Demon", 10, 30, demon};
Character m_squid = { "Squid", 11, 14, squid};

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

        printf("              ");

        mStart = maxLines - m->lines;

        if(line >= mStart)
        {
            printf("%s", m->art[line - mStart]);
        }
        printf("\n");
    }
    printf("======================================================================\n");
}


int main()
{   int choice;
    int randomIndex;
    srand(time(NULL));
    Character* player;

    printf("Choose your character:\n");
    printf("1. Swordsman\n");
    printf("2. Sorcerer\n");
    printf("Select: ");
    scanf("%d", &choice);

    if(choice == 2) player = &c_sorcerer;
    else            player = &c_swordsman;

    printCharacter(player, &m_slime);

    return 0;
}
