#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

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
    "\t\t  __        +---------------------------------------------+   ",//1
    "\t\t (_ \\       |The sun left us. Your spark will vanish next.|  ",//2
    "\t\t   \\ \\      +---------------------------------------------+ ",//4
    "\t\t    \\ \\_/\\/\\/\\/\\_                                       ",//3
    "\t\t     \\           |_                                          ",//5
    "\t\t      \\            |_                                        ",//6
    "\t\t       |             |_                                       ",//7
    "\t\t       | |)  (| |)     \\                                     ",//8
    "\t\t       |_|----|_|'--\\___\\                                   ",//9
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
            printf("     ");
            printf("%s", m->art[line]);

            printf("\n");
    }
    printf("======================================================================\n");
}


int main()
{   int choice;
    int randomIndex;
    srand(time(NULL));
    Character* player;

    CharacterData();

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
