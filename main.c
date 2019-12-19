#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"

int main()
{
    srand(time(NULL));
    printf("========================================\n");
    printf("===================SNAKE================\n");
    printf("========================================\n");
    printf("=Za kazdy zjedzony owoc dostajesz 5 pkt=\n");
    printf("======JABLKO +, POMARANCZ O, BANAN }======");
    printf("========================================\n");

    int sizex = 0, sizey = 0;
    int check;
    char **board;

    //Asking for x size
    while(sizex < 5 || sizex > 15)
    {
        printf("Podaj dlugosc planszy (Max 15, Min 5): ");
        check = scanf("%d", &sizex);
        if(error(check)) return 0;
    }

    //Asking for y size
    while(sizey < 5 || sizey > 15)
    {
        printf("Podaj wysokosc planszy (Max 15, Min 5): ");
        check = scanf("%d", &sizey);
        if(error(check)) return 0;
    }

    //Randomizing head position
    int headx = rand() % sizex;
    int heady = rand() % sizey;

    struct board_t *b = board_generate(sizex, sizey, headx, heady);

    printf("Aby zaczac nacisnij dowolny klawisz\n");
    getchar();


    int score = 0;
    int dead = 0;
    char move = 'w';
    while(getchar() != '\n');
    system("@cls||clear"); //Might not work, it clears console

    //Main loop
    while(move != '0' && dead == 0)
    {
        printf("=====================================\n");
        printf("======Aby zakonczyc nacisnij 0=======\n");
        printf("=====================================\n\n");
        display_board(b);
        printf("\n");
        printf("=====================================\n");
        printf("========ZJEDZONE OWOCE: %d===========\n", score / 5);
        printf("=====================================\n");

        scanf("%c", &move);
        while(getchar() != '\n');
        system("@cls||clear"); //Might not work, it clears console
        if(b -> tail_len && backwards(b, move))
        {
            printf("=====================================\n");
            printf("====NIE MOZESZ SIE RUSZYC DO TYLU====\n");
            printf("=====================================\n");
            Sleep(1000);
        }
        else
            move_player(b, move);

        if(death(b))
            dead = 1;

        if(collide(b))
        {
            score += 5;
            fruit_generator(b);
        }
    }
    //End game output
    system("@cls||clear"); 
    printf("========================================\n");
    printf("==============KONIEC GRY================\n");
    if(dead) printf("===========ZJADLES SWOJ OGON============\n");
    printf("========OSIAGNALES %d PUNKTOW===========\n", score);
    printf("==========ZJADAJAC %d OWOCOW============\n", score / 5);
    printf("========================================\n");
    printf("Wcisnij dowolny klawisz...\n");

    destroy_board(b);
    getchar();
    return 0;
}