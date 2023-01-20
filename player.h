#ifndef PLAYER_H
#define PLAYER_H


struct Player_s;

typedef struct Player_s {
  int wall;//number of wall you can place
  int pos;//pos of the player in the board
} Player;

struct Item_s;
 
typedef struct Item_s {
  Player player;
  Player ia;
  int turn;
  int size; 
  char *board; // board is an array of small int
  int blank;
  float f, g, h; // cost, heuristic, ...
  int depth;
  struct Item_s *parent; // needed for tree structure in game search
  struct Item_s *prev, *next; // needed for chained list 
} Item;


//player == 0 pour joueur
//player == 1 pour ia
void movePlayer(Item *node, int direction);

void moveIA(Item *node, int pos, int p);

//direction == 0 pour horizontal
//direction == 1 pour vertical
//player == 0 pour joueur
//player == 1 pour ia
void putWall(Item *node, int player, int position);

void UnputWall(Item *node, int player, int pos);


#endif 