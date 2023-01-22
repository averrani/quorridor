#ifndef BOARD_H
#define BOARD_H

#include "player.h"

#define RANDINIT()  srand(time(NULL))
#define RANDOM()  ((float)rand() / (float)RAND_MAX)
#define RANDMAX(x)  (int)((float)(x)*rand()/(RAND_MAX+1.0))

#define MAX_BOARD 169//plateau contenant la place pour les murs et les case pour se deplacer 169 289
#define WH_BOARD 13//largeur du plateau avec les murs toujours impair car on peut pas placer 5 13 17
//de murs sur les cotés




Item *initGame();
void initBoard(Item *child, Item *node);
Item *getChildBoard( Item *node, int pos );
Item *getChildBoardPlayer(Item *node, int pos);
int evaluateBoard( Item *node );
void printBoard( Item *board );
int isValidPosition(Item *node, int pos, int player);
int isValidPositionWall(Item *node, int pos);

#endif 