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
  char *board; // board is an array of small int
} Item;

struct list{
  int numElements;
  Item *elt;
  struct list *next;
};
typedef struct list list_t;

Item *nodeAlloc();
void freeItem(Item *node );
void cleanupList( list_t *list );
void initList( list_t *list_p );
list_t * addListe(Item *e,list_t *l);

//player == 0 pour joueur
//player == 1 pour ia
void movePlayer(Item *node, int direction);

void moveIA(Item *node, int pos, int p);

//direction == 0 pour horizontal
//direction == 1 pour vertical
//player == 0 pour joueur
//player == 1 pour ia
void putWall(Item *node, int player, int position);



#endif 