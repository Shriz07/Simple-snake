#ifndef SNAKE_H
#define SNAKE_H

struct head_t{
    int x;
    int y;
};

struct tail_t{
    int x;
    int y;
};

enum fruit_type{
    orange,
    apple,
    banana
};

struct fruit_t{
    int x;
    int y;
    enum fruit_type type;
};

struct board_t{
    char **board;
    int sizex;
    int sizey;
    struct head_t head;
    struct tail_t *tail;
    int tail_len;
    struct fruit_t  fruit;
};

int error(int); //function to handle errors
struct board_t *board_generate(int, int, int , int); //function to generate board
void tail_generate(struct board_t *, int, int); //Allocate memory for tail
void display_board(struct board_t *); //funcition displaying board
void move_player(struct board_t *, char); //function to move player in given direction
void fruit_generator(struct board_t *); //function to generate fruit on board
int collide(struct board_t *); //function to detect collision between head and fruit
void destroy_board(struct board_t *); //funcion to free memory
int death(struct board_t *); //function to detect death
int backwards(struct board_t *, char); //function to detect if player want to move backwards

#endif