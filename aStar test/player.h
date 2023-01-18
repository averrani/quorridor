#ifndef PLAYER_H
#define PLAYER_H

struct Player_s;

typedef struct Player_s {
  int wall;//number of wall you can place
  int pos;//pos of the player in the board
} Player;




/*
 * Deplace le pion du player selon la direction indiquée en paramètre
 * @param position Coordonée du mur (représenté en -1 sur la grille)
 * @param direction Direction de déplacement du joueur : 
 * 0 -> en haut; 1 -> a droite; 2 -> en bas; 3 -> a gauche
 
void putWall(int position, int direction);
*/
#endif 