#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"

int backwards(struct board_t *b, char move)
{
    if(move == 'a') //Move left
    {
        if(b -> head.x - 1 == b -> tail -> x)
            return 1; 
    }
    else if(move == 'd') //Move right
    {
        if(b -> head.x + 1 == b -> tail -> x)
            return 1;
    }
    else if(move == 'w') //Move forward
    {
        if(b -> head.y - 1 == b -> tail -> y)
            return 1;
    }
    else if(move == 's') //Move backwards
    {
        if(b -> head.y + 1 == b -> tail -> y)
            return 1;
    }
    return 0;
}

int collide(struct board_t *b)
{
    return b -> head.x == b -> fruit.x && b -> head.y == b -> fruit.y;
}

int death(struct board_t *b)
{
    for(int i = b -> tail_len - 1; i > 0; i--)
    {
        if((b -> tail + i) -> x == b -> head.x && (b -> tail + i) -> y == b -> head.y)
            return 1; 
    }
    return 0;
}

void fruit_generator(struct board_t *b)
{
    b -> fruit.x = b -> head.x;
    b -> fruit.y = b -> head.y;
    int tail = 0;
    while((b -> fruit.x == b -> head.x || b -> fruit.y == b -> head.y) || tail)
    {
        tail = 0;
        b -> fruit.x = rand() % b -> sizex;
        b -> fruit.y = rand() % b -> sizey;
        for(int i = b -> tail_len - 1; i > 0; i--)
        {
            if((b -> tail + i) -> x == b -> fruit.x && (b -> tail + i) -> y == b -> fruit.y)
            {
                tail = 1;
                break;
            }
        }
    }
    int type = rand() % 3;
    b -> fruit.type = type;
}

void move_player(struct board_t *b, char move)
{
    int x = 0, y = 0;
    if(b -> tail_len == 0)
    {
        x = b -> head.x;
        y = b -> head.y;
    }
    else
    {
        x = (b -> tail + b -> tail_len - 1) -> x;
        y = (b -> tail + b -> tail_len - 1) -> y;
    }

    for(int i = b -> tail_len - 1; i > 0; i--)
    {
        (b -> tail + i) -> x = (b -> tail + i - 1) -> x;
        (b -> tail + i) -> y = (b -> tail + i - 1) -> y;
    }
    if(b -> tail_len)
    {
        (b -> tail) -> x = b -> head.x;
        (b -> tail) -> y = b -> head.y;
    }

    if(move == 'w')
    {
        if(b -> head.y == 0)
            b -> head.y = b -> sizey - 1;
        else
            b -> head.y--;
    }
    if(move == 's')
    {
        if(b -> head.y == b -> sizey - 1)
            b -> head.y = 0;
        else
            b -> head.y++;
    }
    if(move == 'a')
    {
        if(b -> head.x == 0)
            b -> head.x = b -> sizex - 1;
        else
            b -> head.x--;
    }
    if(move == 'd')
    {
        if(b -> head.x == b-> sizex - 1)
            b -> head.x = 0;
        else
            b -> head.x++;
    }

    if(collide(b))
    {
        tail_generate(b, x, y);
    }
}

struct board_t *board_generate(int x, int y, int hx, int hy)
{
    struct board_t *b = malloc(sizeof(struct board_t));

    b -> board = malloc(sizeof(char *) * x);
    if(b -> board == NULL)
        return NULL;

    for(int i = 0; i < x; i++)
    {
        *(b -> board + i) = malloc(sizeof(char) * y);
        if(*(b -> board + i) == NULL) return NULL;
    }

    for(int i = 0; i < x ; i++)
    {
        for(int j = 0; j < y; j++)
        {
            *(*(b -> board + j) + i) = '#';
        }
    }

    *(*(b -> board + hx) + hy) = '#';

    b -> sizex = x;
    b -> sizey = y;
    b -> head.x = hx;
    b -> head.y = hy;
    b -> tail_len = 0;

    b -> tail = malloc(sizeof(struct tail_t) * b -> sizex * b -> sizey);

    fruit_generator(b);
    
    return b;
}

void tail_generate(struct board_t *b, int x, int y)
{
    (b -> tail + b -> tail_len) -> x = x;
    (b -> tail + b -> tail_len) -> y = y;
    b -> tail_len++;
}

void display_board(struct board_t *b)
{
    for(int i = 0; i < b -> sizex; i++)
    {
        printf("            ");
        for(int j = 0; j < b -> sizey; j++)
        {
            int done = 0;
            if(i == b -> head.y && j == b -> head.x)
            {
                printf("@");
                done = 1;
            }
            else if(i == b -> fruit.y && j == b -> fruit.x)
            {
                if(b -> fruit.type == orange)
                    printf("O");
                if(b -> fruit.type == apple)
                    printf("+");
                if(b -> fruit.type == banana)
                    printf("}");
                done = 1;
            }
            for(int k = 0; k < b -> tail_len; k++)
            {
                if(i == (b -> tail + k) -> y && j == (b -> tail + k) -> x)
                {
                    printf("~");
                    done = 1;
                }
            }
            if(!done)
                printf("%c",*(*(b -> board + j) + i));
        }
        printf("\n");
    }
}

int error(int check)
{
    if(!check)
    {
        printf("Input error");
        return 1;
    }
    return 0;
}

void destroy_board(struct board_t *b)
{
    if(b != NULL)
    {
        for(int i = 0; i < b -> sizex; i++)
        {
            free(*(b -> board + i));
        }
        free(b -> tail);
        free(b -> board);
        free(b);
    }
}