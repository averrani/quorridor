#ifndef ITEM_H
#define ITEM_H

#include "Player.h"


typedef struct Item_s {
  Player player1;
  Player player2;
  int size; 
  char *board; // board is an array of small int
  int blank;
  float f, g, h; // cost, heuristic, ...
  int depth;
  struct Item_s *parent; // needed for tree structure in game search
  struct Item_s *prev, *next; // needed for chained list 
} Item;

#endif 
