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

  node->player.pos = WH_BOARD*(WH_BOARD-1) + WH_BOARD/2;   // define pos of player
  node->turn = 0;  // first turn to player
  node->player.wall = 10; // number of wall

  node->ia.pos = WH_BOARD/2; // define pos of ia
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
  if (node->player.pos >= 0 && node->player.pos < WH_BOARD)
  {
    printf("Player win");
    return -10;
  }
  if (node->ia.pos >= WH_BOARD*(WH_BOARD+1) && node->ia.pos < MAX_BOARD)
  {
    printf("ia win");
    return 10;
  } 
  return 0; 
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
}


//player = 0 pour le joueur
//player = 1 pour l'ia
int isValidPosition(Item *node, int pos, int player){
  //test si pos est la pos d'un mur
  if(node->board[pos] == -1 || node->board[pos] == -2)
    return 0;

  if(player == 0){ //test pour le joueur    
    //tests de deplacements autorisés
    if(pos == node->player.pos + 2 || pos == node->player.pos - 2 || pos == node->player.pos + (2*WH_BOARD) || pos == node->player.pos - (2*WH_BOARD)){

      if(pos == node->ia.pos) //test pr savoir si la case contient le joueur adverse
        return 1;
      if(pos == node->player.pos + 2 && node->board[pos - 1] == -1 && node->player.pos%WH_BOARD != WH_BOARD-1){ // test pr savoir si y'a un mur a droite
        return 1;
      }
      if(pos == node->player.pos - 2 && node->board[pos + 1] == -1 && node->player.pos%WH_BOARD != 0){ // test pr savoir si y'a un mur a gauche
        return 1;
      }
      if(pos == node->player.pos +(2*WH_BOARD) && node->board[pos - WH_BOARD] == -1 && node->player.pos/WH_BOARD != WH_BOARD-1){ // test pr savoir si y'a un mur en bas
        return 1;
      }
      if(pos == node->player.pos -(2*WH_BOARD) && node->board[pos + WH_BOARD] == -1 && node->player.pos/WH_BOARD != 0){ // test pr savoir si y'a un mur en haut
        return 1;
      }
    }
      return 0;

  }else if(player == 1){ //test pour l'ia
    
    //tests de deplacements autorisés
    if(pos == node->ia.pos + 2 || pos == node->ia.pos - 2 || pos == node->ia.pos + (2*WH_BOARD) || pos == node->ia.pos - (2*WH_BOARD)){

      if(pos == node->player.pos) //test pr savoir si la case contient le joueur adverse
        return 1;
      if(pos == node->ia.pos + 2 && node->board[pos - 1] == -1 && node->ia.pos%WH_BOARD != WH_BOARD-1){ // test pr savoir si y'a un mur a droite et si on sort pas du board
        return 1;
      }
      if(pos == node->ia.pos - 2 && node->board[pos + 1] == -1 && node->ia.pos%WH_BOARD != 0){ // test pr savoir si y'a un mur a gauche
        return 1;
      }
      if(pos == node->ia.pos +(2*WH_BOARD) && node->board[pos - WH_BOARD] == -1 && node->ia.pos/WH_BOARD != WH_BOARD-1){ // test pr savoir si y'a un mur en bas
        return 1;
      }
      if(pos == node->ia.pos -(2*WH_BOARD) && node->board[pos + WH_BOARD] == -1 && node->ia.pos/WH_BOARD != 0){ // test pr savoir si y'a un mur en haut
        return 1;
      }
    }
    
    return 0;
  }
}

//dir = 0 horizontal
//dir = 1 vertical
int isValidPositionWall(Item *node, int pos){
  int i,j;

  if(node->board[pos+1] != -1 ){
    if(node->board[pos] == -1 && node->board[pos+WH_BOARD] == -1 && node->board[pos+2*WH_BOARD] == -1 ){
      for(j=0; j<WH_BOARD; j=j+2){ // on parcourt uniquement les lignes avec les -1 (murs)
          for(i=1; i<WH_BOARD; i=i+2){ 
            if(pos == i +(j*WH_BOARD)){ //voir screen 
                return 1;
            }
          }
      }
      return 0;
    }
    return 0;// ne pas enlever important
  }else{
    if(node->board[pos] == -1 && node->board[pos+1] == -1 && node->board[pos+2] == -1 ){
      for(j=1; j<WH_BOARD; j=j+2){ // on parcourt uniquement les lignes avec les -1 (murs)
          for(i=0; i<WH_BOARD; i=i+2){ 
            if(pos == i +(j*WH_BOARD)){ //voir screen 
                return 1;
            }
          }
      }
      return 0;
    }
    return 0;// ne pas enlever important
  }
}


// Return a new item where a new queen is added at position pos if possible. NULL if not valid
Item *getChildBoard(Item *node, int pos)
{
  Item *child_p = NULL;

  if (isValidPosition(node, pos, 1) == 1) //deplacement normal 
  {
    /* allocate and init child node */
    child_p = nodeAlloc();
    initBoard(child_p, node->board);
    /* Make move */
    moveIA(child_p, pos);

    child_p->depth = node->depth +1 ;
    
		/* link child to parent for backtrack */
    child_p->parent = node;
  }

  if (isValidPositionWall(node, pos) == 1 && node->ia.wall > 0 ) //deplacement en sautant par dessus le joueur
  {
    /* allocate and init child node */
    child_p = nodeAlloc();
    initBoard(child_p, node->board);
    /* Make move */

    putWall(child_p, 1, pos);
    child_p->ia.wall = node->ia.wall - 1;

    child_p->depth = node->depth +1 ;
    
		/* link child to parent for backtrack */
    child_p->parent = node;
  }

  return child_p;
}
