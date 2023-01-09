#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Item.h"
#include "Board.h"


struct Player_s;

typedef struct Player_s {
  int turn; //1 si c'est au tour du Player, 0 si c'est a l'adversaire de jouer
  int wall;//nombre de mur restant a placer, valeur initialisée a 10 en début de partie
  int pos;//position du Player sur la grille
} Player;


void putStick(Item *node , int pos);  // placer un mur 
void makeMove(Item *node , int pos);  // déplacer son pion 








#endif 