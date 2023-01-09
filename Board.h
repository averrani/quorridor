#ifndef BOARD_H
#define BOARD_H

#include "List.h"
#include "Player.h"


// #define RANDINIT()  srand(time(NULL))
// #define RANDOM()  ((float)rand() / (float)RAND_MAX)
// #define RANDMAX(x)  (int)((float)(x)*rand()/(RAND_MAX+1.0))

#define MAX_BOARD 289 //plateau contenant la place pour les murs et les case pour se deplacer
#define WH_BOARD 17//largeur du plateau avec les murs toujours impair car on peut pas placer 
//de murs sur les cotés




Item *initGame();
void initBoard(Item *node, char *board);
Item *getChildBoard( Item *node, int pos );
double evaluateBoard( Item *node );
int isValidPosition(Item *node ,int pos );
void printBoard( Item *board );


#endif