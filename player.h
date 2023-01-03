#ifndef PLAYER_H
#define PLAYER_H

struct Player_s;



typedef struct Player_s {
  int turn; //0 if its not ur turn 1 if its ur turn
  int wall;//number of wall you can place
  int pos;//pos of the player in the board
} Player;

#endif 