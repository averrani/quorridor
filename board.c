#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"

// Initialize a new Game for the nQueens problem: an empty board..
Item *initGame()
{

  int i;
  Item *node;

  Player player1;
  Player player2;

  player1.pos=9;//define pos of player1
  player1.turn=1;//first turn to player1
  player1.wall=10;//number of wall

  player2.pos=280; //define pos of player2
  player2.turn=0;//first turn to player1
  player2.wall=10;//number of wall



  char *initial = (char *)malloc(MAX_BOARD * sizeof(char));
  for (int i = 0; i < MAX_BOARD; i=i+2)
    {
      initial[i] = 0;//define where the player can move
    }
  for ( int i = 1; i < MAX_BOARD; i=i+2)
  {
    initial[i]=-1; //define where the player can place wall
  }
  
  node = nodeAlloc();
  initial[player1.pos]=1;
  initial[player2.pos]=2;
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
  // int nb = WH_BOARD, i;  
  if (node->board[MAX_BOARD-1])
  {
    return 1;
  }
  /*for (i = 0; i < MAX_BOARD; i++)
  {
    if (node->board[i] == 1)
    {
      nb--;
    }
  }
  return nb;*/
}

//START CHANGE
// initialize node's state from a given board
void initBoard(Item *node, char *board)
{
  assert(node);
  int i;

  node->size = MAX_BOARD;
  node->board = calloc(MAX_BOARD, sizeof(char));
if (board!=NULL)
{
 for (i = 0; i < MAX_BOARD; i++)
  {
    node->board[i] = board[i];
  }
}
else{
  for ( i = 0; i < MAX_BOARD; i++)
  {
    node->board[i]=0;
  }
  

}

/*for (i = 0; i < MAX_BOARD; i++)
  {
    node->board[i] = board[i];
  }*/  
}

// Return 1 if knight is at the last 
// 


// Test if position pos is valid with respect to node's state
// nQueens -> not same row ; not same column ; not same diagonal
int isValidPosition(Item *node, int pos)
{
  int ii = pos / WH_BOARD;
  int jj = pos % WH_BOARD;
  // la reine a testé est en position node->board[ii][jj]

  for (int i = 0; i < WH_BOARD; i++)
  {
    for (int j = 0; j < WH_BOARD; j++)
    {
      /*if (j == jj && node->board[i * WH_BOARD + j] == 1 && )
      {
        return 0;
      }
      else if (i == ii && node->board[i * WH_BOARD + j] == 1)
      {
        return 0;
      }*/
     
      if ((abs(ii - i) * abs(j - jj))==2 && node->board[i * WH_BOARD + j] == 1)
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
    child_p->board[pos] = 1 ;
    /* link child to parent for backtrack */
    child_p->parent = node;

    
    /*incrémenter la profondeur de 1*/
    child_p->depth++;
  }

  return child_p;
}
