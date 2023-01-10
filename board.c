#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"

// Initialize a new Game for the nQueens problem: an empty board..
Item *initGame()
{

  int i,j;
  Item *node;
  node = nodeAlloc();

  node->player1.pos = 8;  // define pos of player1
  node->player1.turn = 1;  // first turn to player1
  node->player1.wall = 10; // number of wall

  node->player2.pos = 314; // define pos of player2
  node->player2.turn = 0;  // first turn to player1
  node->player2.wall = 10; // number of wall

  char *initial = (char *)malloc(MAX_BOARD * sizeof(char));

  int ii, jj;
  for (i=0; i<MAX_BOARD; i++) {
    if(i%2 == 0){
      initial[i] = 0;
    }
    else
      initial[i] = -1;
    ii = i / WH_BOARD;
	  jj = i % WH_BOARD;

    if((jj+1)%2 == 0){
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

  
  initial[node->player1.pos] = 1;
  initial[node->player2.pos] = 2;
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
  if (0 < node->player2.pos < 17)
  {
    printf("PLayer 2 win");
    return 1;
  }
  if (305 < node->player2.pos < 322)
  {
    printf("PLayer 1 win");
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



  if (board==NULL)
  {

  node->player1.pos = 8;  // define pos of player1
  node->player1.turn = 1;  // first turn to player1
  node->player1.wall = 10; // number of wall

  node->player2.pos = 314; // define pos of player2
  node->player2.turn = 0;  // first turn to player1
  node->player2.wall = 10; // number of wall


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

// Return 1 if knight is at the last
//

// Test if position pos is valid with respect to node's state
// nQueens -> not same row ; not same column ; not same diagonal
int isValidPosition(Item *node, int pos)
{
  int ii = pos / WH_BOARD;
  int jj = pos % WH_BOARD;
  // test a qui c'ets le tour
  // testé si la position a testé est derriere le player1 ou a droite du player1 avant de testé si y'a des murs
    // test si y'a pas de mur en premier puis test si y'a pas le joueur adverse sur la case
    //-2 where there is a wall
    // 1 where there is a player
  if (node->player1.turn == 1)
  {
    if (abs(node->player1.pos - pos) == 2 || abs(node->player1.pos - pos) == 34)
    {

      if (node->player1.pos - pos == 2 && node->player1.pos + 1 != -2) // test 1st legal move
      {
        return 1;
      }
      if (node->player1.pos - pos == -2 && node->player1.pos - 1 != -2) // test 2nd legal move
      {
        return 1;
      }
      if (node->player1.pos - pos == 34 && node->player1.pos + 17 != -2) // test 3rd legal move
      {
        return 1;
      }
      if (node->player1.pos - pos == -34 && node->player1.pos - 17 != -2) // test 4th legal move
      {
        return 1;
      }
    }
    
  }
  
  else
  {
     if (abs(node->player2.pos - pos) == 2 || abs(node->player2.pos - pos) == 34)
    {

      if (node->player2.pos - pos == 2 && node->player2.pos - 1 != -2) // test 1st legal move
      {
        return 1;
      }
      if (node->player2.pos - pos == -2 && node->player2.pos + 1 != -2) // test 2nd legal move
      {
        return 1;
      }
      if (node->player2.pos - pos == 34 && node->player2.pos - 17 != -2) // test 3rd legal move
      {
        return 1;
      }
      if (node->player2.pos - pos == -34 && node->player2.pos + 17 != -2) // test 4th legal move
      {
        return 1;
      }
    }
  }
  return 0;
}

// Return a new item where a new queen is added at position pos if possible. NULL if not valid
Item *getChildBoard(Item *node, int pos)
{
  Item *child_p = NULL;

  if (isValidPosition(node, pos))
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
