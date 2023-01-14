#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"

// Initialize a new Game for the nQueens problem: an empty board..
Item *initGame()
{

  int i, j;
  Item *node;
  node = nodeAlloc();

  node->player.pos = WH_BOARD*(WH_BOARD+1) + WH_BOARD/2;   // define pos of player
  node->player.turn = 1;  // first turn to player
  node->player.wall = 10; // number of wall

  node->ia.pos = WH_BOARD/2; // define pos of ia
  node->ia.turn = 0;  // first turn to player
  node->ia.wall = 10; // number of wall

  char *initial = (char *)malloc(MAX_BOARD * sizeof(char));

  int ii, jj;
  for (i = 0; i < MAX_BOARD; i++)
  {
    if (i % 2 == 0)
    {
      initial[i] = 0;
    }
    else
      initial[i] = -1;
    ii = i / WH_BOARD;
    jj = i % WH_BOARD;

    if ((jj + 1) % 2 == 0)
    {
      initial[i] = -1;
    }
  }

  /*for (int i = 0; i < MAX_BOARD; i = i + 2)
  {
    initial[i] = 0; // define where the player can move I START AT 0 AND I+2
  }
  for (int i = 1; i < MAX_BOARD; i = i + 2)
  {
    initial[i] = -1; // define where the player can place wall I START AT 1 AND I+2
  }
  */

  initial[node->player.pos] = 1;
  initial[node->ia.pos] = 2;
  initBoard(node, initial);

  node->depth = 0;

  return node;
}

// print a board
void printBoard(Item *node)
{
  assert(node);
  printf("\n");
  for (int j = 0; j < WH_BOARD; j++)
    if (j == 0)
      printf(" ___");
    else
      printf("____");
  printf("\n");
  for (int i = 0; i < MAX_BOARD; i++)
  {
    if (i % WH_BOARD == 0)
      printf("|");
    if (node->board[i] == 0)
      printf("   |");
    else
      printf("%2d |", node->board[i]);
    if (((i + 1) % WH_BOARD) == 0)
    {
      printf("\n");
      for (int j = 0; j < WH_BOARD; j++)
        if (j == 0)
          printf(" ___");
        else
          printf("____");
      printf("\n");
    }
  }
  printf("\n");
}

double evaluateBoard(Item *node)
{
  if (0 < node->player.pos < WH_BOARD)
  {
    printf("Player win");
    return 1;
  }
  if (305 < node->ia.pos < 322)
  {
    printf("ia win");
    return 1;
  }
}

// START CHANGE
//  initialize node's state from a given board
void initBoard(Item *node, char *board)
{
  assert(node);
  int i;

  node->size = MAX_BOARD;
  node->board = calloc(MAX_BOARD, sizeof(char));
  if (board != NULL)
  {
    for (i = 0; i < MAX_BOARD; i++)
    {
      node->board[i] = board[i];
    }
  }

  if (board == NULL)
  {

  node->player.pos = WH_BOARD*(WH_BOARD+1) + WH_BOARD/2;  // define pos of player
  node->player.turn = 1;  // first turn to player
  node->player.wall = 10; // number of wall

  node->ia.pos = WH_BOARD/2; // define pos of ia
  node->ia.turn = 0;  // first turn to player
  node->ia.wall = 10; // number of wall


int ii, jj;
  for (i=0; i<MAX_BOARD; i++) {
    if(i%2 == 0){
      node->board[i] = 0;
    }
    else
      node->board[i] = -1;
    ii = i / WH_BOARD;
	  jj = i % WH_BOARD;

    if((jj+1)%2 == 0){
      node->board[i] = -1;
    }
  }
  
}

}

/*
// Test if position pos is valid with respect to node's state
// nQueens -> not same row ; not same column ; not same diagonal
int isValidPosition(Item *node, int pos)
{
  int ii = pos / WH_BOARD;
  int jj = pos % WH_BOARD;
  // test a qui c'ets le tour
  // testé si la position a testé est derriere le player ou a droite du player avant de testé si y'a des murs
  // test si y'a pas de mur en premier puis test si y'a pas le joueur adverse sur la case
  //-2 where there is a wall
  // 1 where there is a player
  if (node->player.turn == 1)
  {
    if (abs(node->player.pos - pos) == 2 || abs(node->player.pos - pos) == 34)
    {

      if (node->player.pos - pos == 2 && node->player.pos + 1 != -2) // test 1st legal move
      {
        return 1;
      }
      if (node->player.pos - pos == -2 && node->player.pos - 1 != -2) // test 2nd legal move
      {
        return 1;
      }
      if (node->player.pos - pos == 34 && node->player.pos + WH_BOARD != -2) // test 3rd legal move
      {
        return 1;
      }
      if (node->player.pos - pos == -34 && node->player.pos - WH_BOARD != -2) // test 4th legal move
      {
        return 1;
      }
    }
  }
  
  else
  {
    if (abs(node->ia.pos - pos) == 2 || abs(node->ia.pos - pos) == 34)
    {

      if (node->ia.pos - pos == 2 && node->ia.pos - 1 != -2) // test 1st legal move
      {
        return 1;
      }
      if (node->ia.pos - pos == -2 && node->ia.pos + 1 != -2) // test 2nd legal move
      {
        return 1;
      }
      if (node->ia.pos - pos == 34 && node->ia.pos - WH_BOARD != -2) // test 3rd legal move
      {
        return 1;
      }
      if (node->ia.pos - pos == -34 && node->ia.pos + WH_BOARD != -2) // test 4th legal move
      {
        return 1;
      }
    }
  }
  return 0;
}
*/

//player = 0 pour le joueur
//player = 1 pour l'ia
int isValidPosition(Item *node, int pos, int player){
  
  //test si pos est la pos d'un mur
  if(node->board[pos] == -1 || node->board[pos] == -2)
    return 0;

  if(player == 0){ //test pour le joueur    
    //tests de deplacements autorisés
    if(pos == node->player.pos + 2 || pos == node->player.pos - 2 || pos == node->player.pos + WH_BOARD || pos == node->player.pos - WH_BOARD){

      if(pos == node->ia.pos) //test pr savoir si la case contient le joueur adverse
      return 2;
      if(pos == node->player.pos + 2 && node->board[pos - 1] == -1 ){ // test pr savoir si y'a un mur a droite
        return 1;
      }
      if(pos == node->player.pos - 2 && node->board[pos + 1] == -1 ){ // test pr savoir si y'a un mur a gauche
        return 1;
      }
      if(pos == node->player.pos +(2*WH_BOARD) && node->board[pos - WH_BOARD] == -1 ){ // test pr savoir si y'a un mur en bas
        return 1;
      }
      if(pos == node->player.pos -(2*WH_BOARD) && node->board[pos + WH_BOARD] == -1 ){ // test pr savoir si y'a un mur en haut
        return 1;
      }
    }

  }else if(player == 1){ //test pour l'ia
    
    //tests de deplacements autorisés
    if(pos == node->ia.pos + 2 || pos == node->ia.pos - 2 || pos == node->ia.pos + (2*WH_BOARD) || pos == node->ia.pos - (2*WH_BOARD)){

      if(pos == node->player.pos) //test pr savoir si la case contient le joueur adverse
        return 2;
      if(pos == node->ia.pos + 2 && node->board[pos - 1] == -1 ){ // test pr savoir si y'a un mur a droite
        return 1;
      }
      if(pos == node->ia.pos - 2 && node->board[pos + 1] == -1 ){ // test pr savoir si y'a un mur a gauche
        return 1;
      }
      if(pos == node->ia.pos +(2*WH_BOARD) && node->board[pos - WH_BOARD] == -1 ){ // test pr savoir si y'a un mur en bas
        return 1;
      }
      if(pos == node->ia.pos -(2*WH_BOARD) && node->board[pos + WH_BOARD] == -1 ){ // test pr savoir si y'a un mur en haut
        return 1;
      }
    }
    
    return 0;
  }
  

}

int isValidPositionWall(Item *node, int pos, int dir)
{

  if (node->board[pos] == -1)
  {
    if (dir == 0) // cas horizontal.
    {
      if (node->board[pos + 1] == -1 && node->board[pos - 1] == -1)
      {
        return 1;
      }
    }
    else
    {
      if (node->board[pos + WH_BOARD] == -1 && node->board[pos - WH_BOARD] == -1)
      {
        return 1;
      }
    }
  }
}

// Return a new item where a new queen is added at position pos if possible. NULL if not valid
Item *getChildBoard(Item *node, int pos)
{
  Item *child_p = NULL;

  if (isValidPosition(node, pos, 0))
  {
    /* allocate and init child node */
    child_p = nodeAlloc();
    initBoard(child_p, NULL);
    /* Make move */
    child_p->board[pos] = 1;
    /* link child to parent for backtrack */
    child_p->parent = node;

    /*incrémenter la profondeur de 1*/
    child_p->depth++;
  }

  return child_p;
}
