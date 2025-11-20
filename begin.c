#include <stdio.h>
#include <windows.h>

void card_setting(void);
void game(void);
void learn(void);

void main()
{
    int choose;
    while(1)
    {
      printf("WHAT MODE DO YOU WANT?\n");
      printf("1 card setting\n");
      printf("2 game\n");
      printf("3 learn\n");
      printf("pick the number: ");
      fflush(stdin);
      scanf("%d",&choose);

      switch(choose)
      {
      case 1:
        system("cls");
        card_setting();
        break;
      case 2:
        system("cls");
        game();
        break;
      case 3:
        system("cls");
        learn();
        break;
      default:
        system("cls");
        printf("TRY AGAIN\n");
        Sleep(400);
        system("cls");
        continue;
      }
      break;
    }
}

void card_setting()
{
    printf("CARD SETTING\n");
}

void game()
{
    printf("GAME\n");
}

void learn()
{
    printf("LEARN\n");
}

