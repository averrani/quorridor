#ifndef PLAYER_H
#define PLAYER_H

struct Player_s;



typedef struct Player_s {
  int turn; 
  int wall;//number of wall you can place
  int pos;
} Player;

#endif 