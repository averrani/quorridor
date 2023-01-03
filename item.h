#ifndef ITEM_H
#define ITEM_H

struct Item_s;

const int size=289; // size of board (< 255)

typedef struct Item_s {
  int wall;//number of wall you can place
  char *board; // board is an array of small int
  int blank;
  float f, g, h; // cost, heuristic, ...
  int depth;
  struct Item_s *parent; // needed for tree structure in game search
  struct Item_s *prev, *next; // needed for chained list 
} Item;

#endif 
