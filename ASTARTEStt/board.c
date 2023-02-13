#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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

  assert(node);

  node->size = MAX_BOARD;
  node->board = calloc(MAX_BOARD, sizeof(char));
  if (initial != NULL)
  {
    for (i = 0; i < MAX_BOARD; i++)
    {
      node->board[i] = initial[i];
    }
  }

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

int evaluateBoard(Item *node)
{
  if (node->player.pos >= 0 && node->player.pos < WH_BOARD)
    return -10;
  if (node->ia.pos >= WH_BOARD*(WH_BOARD+1) && node->ia.pos < MAX_BOARD)
    return 10;
  return 0; 
}

// START CHANGE
//  initialize node's state from a given board
void initBoard(Item *child, Item *node)
{
  //assert(child);
  int i;

  // child->size = MAX_BOARD;
  child->board = calloc(MAX_BOARD, sizeof(char));

  for (i = 0; i < MAX_BOARD; i++)
  {
    child->board[i] = node->board[i];
  }

  child->player.pos = node->player.pos;
  child->player.wall = node->player.wall;

  child->ia.pos = node->ia.pos;
  child->ia.wall = node->ia.wall;
}


//player = 0 pour le joueur
//player = 1 pour l'ia
int isValidPosition(Item *node, int pos, int player){
  //test si pos est la pos d'un mur
  if(node->board[pos] == -1 || node->board[pos] == -2)
    return 0;
  
  if(player == 0){ //test pour le joueur    
    //tests de deplacements autorisés
    if(pos == node->player.pos)
      return 0;
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
    if(pos == node->ia.pos)
      return 0;
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
  
  if (isValidPosition(node, pos, 1)) //deplacement normal 
  {
    /* allocate and init child node */
    child_p = nodeAlloc();
    initBoard(child_p, node);
    /* Make move */
    moveIA(child_p, pos, 0);

    child_p->depth = node->depth +1 ;
    
		/* link child to parent for backtrack */
    child_p->parent = node;
  }else

  if (isValidPositionWall(node, pos) && node->ia.wall > 0 ) //deplacement en sautant par dessus le joueur
  {
    /* allocate and init child node */
    child_p = nodeAlloc();
    initBoard(child_p, node);
    /* Make move */

    putWall(child_p, 1, pos);
    child_p->ia.wall = node->ia.wall - 1;

    child_p->depth = node->depth +1 ;
    
		/* link child to parent for backtrack */
    child_p->parent = node;
  }

  return child_p;
}

Item *getChildBoardPlayer(Item *node, int pos)
{
  Item *child_p = NULL;
  int direction;
  if (isValidPosition(node, pos, 0)) //deplacement normal 
  {
    /* allocate and init child node */
    child_p = nodeAlloc();
    initBoard(child_p, node);
    /* Make move */
    
    moveIA(child_p, pos, 1);

    child_p->depth = node->depth +1 ;
    
		/* link child to parent for backtrack */
    child_p->parent = node;
  }else

  if (isValidPositionWall(node, pos) && node->player.wall > 0 ) 
  {
    /* allocate and init child node */
    child_p = nodeAlloc();
    initBoard(child_p, node);
    /* Make move */

    putWall(child_p, 0, pos);

    child_p->depth = node->depth +1 ;
    
		/* link child to parent for backtrack */
    child_p->parent = node;
  }

  return child_p;
}

// lastmove sert à savoir c'était quoi le dernier coup pour séviter qu'il tourne en rond en ne tournant que a droite par exemple *Mettre 0 pour la premiere fois on utilise la fonction pour l'instant fais uniquement pour le joueur commencant à la fin du board
// 0 tout droit, 1 a gauche, 2 a droite,3 derriere

/*posorigin : position du joueur
  player :  IA ou joueur
  lastmove : set to 0 for first loop
  depth: set to 0 for first loop
  node : node to test 
*/
int isPathAvailable(Item *node, int posorigin, int player, int lastmove, int depth) //node
{                                                                        
  // c'est une manière de prioriser certaines instructions plutot que d'autre
  if (evaluateBoard(node))
  {
    return 1;
  }
  if (depth>10000)
  {
    return 0;
  }
  
  

  if (player == 1) // start at the end of the board
  {
    if (lastmove == 0)
    {
      if (!evaluateBoard(node)) // je sais pas comment mettre un nombre d'itération max
      {
        if (isValidPosition(node, posorigin - WH_BOARD, 1))
        {
          node->board[posorigin - WH_BOARD] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin - WH_BOARD, player, 0,depth);
        }
        if (isValidPosition(node, posorigin - 2, 1))
        {
          node->board[posorigin - 2] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin - 2, player, 1,depth);
        }

        if (isValidPosition(node, posorigin + 2, 1))
        {
          node->board[posorigin + 2] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin + 2, player, 2,depth);
        }

        // aller en arriere
        if (isValidPosition(node, posorigin + WH_BOARD, 1))
        {
          node->board[posorigin + WH_BOARD] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin + WH_BOARD, player, 3,depth);
        }
      }
    }

    if (lastmove == 1)
    {
      if (!evaluateBoard(node)) // je sais pas comment mettre un nombre d'itération max
      {
        int a = (int)rand() % 2;
        if (isValidPosition(node, posorigin - WH_BOARD, 1))
        {
          node->board[posorigin - WH_BOARD] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin - WH_BOARD, player, 0,depth);
        }
        if (isValidPosition(node, posorigin - 2, 1))
        {
          node->board[posorigin - 2] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin - 2, player, 1,depth);
        }

        if (isValidPosition(node, posorigin + WH_BOARD, 1))
        {
          node->board[posorigin + WH_BOARD] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin + WH_BOARD, player, 3,depth);
        }

        // aller à droite == revenir sur nos pas
        if (isValidPosition(node, posorigin + 2, 1))
        {
          node->board[posorigin + 2] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin + 2, player, 2,depth);
        }
      }
    }

    if (lastmove == 2)
    {
      if (!evaluateBoard(node)) // je sais pas comment mettre un nombre d'itération max
      {
        int a = (int)rand() % 2;
        if (isValidPosition(node, posorigin - WH_BOARD, 1))
        {
          node->board[posorigin - WH_BOARD] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin - WH_BOARD, player, 0,depth);
        }

        if (isValidPosition(node, posorigin + WH_BOARD, 1))
        {
          node->board[posorigin + WH_BOARD] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin + WH_BOARD, player, 3,depth);
        }

        if (a == 1)
        {
          if (isValidPosition(node, posorigin + 2, 1))
          {
            node->board[posorigin + 2] = 1;
            node->board[posorigin] = 0;

            return isPathAvailable(node, posorigin + 2, player, 2,depth);
          }
        }
        else
        {
          if (isValidPosition(node, posorigin - 2, 1))
          {
            node->board[posorigin - 2] = 1;
            node->board[posorigin] = 0;

            return isPathAvailable(node, posorigin - 2, player, 1,depth);
          }
        }
      }
    }

    if (lastmove == 3)
    {
      if (!evaluateBoard(node)) // je sais pas comment mettre un nombre d'itération max
      {
        // un peu de rand pour faire genre c'est une ia
        int a = (int)rand() % 2;
        if (a == 1)
        {
          if (isValidPosition(node, posorigin + 2, 1))
          {
            node->board[posorigin + 2] = 1;
            node->board[posorigin] = 0;

            return isPathAvailable(node, posorigin + 2, player, 2,depth);
          }
        }
        else
        {
          if (isValidPosition(node, posorigin - 2, 1))
          {
            node->board[posorigin - 2] = 1;
            node->board[posorigin] = 0;

            return isPathAvailable(node, posorigin - 2, player, 1,depth);
          }
        }

        // pas envie de passer notre temps à aller derriere
        if (isValidPosition(node, posorigin + WH_BOARD, 1))
        {
          node->board[posorigin + WH_BOARD] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin + WH_BOARD, player, 3,depth);
        }
        // aller tout droit = revenir sur nos pas
        if (isValidPosition(node, posorigin - WH_BOARD, 1))
        {
          node->board[posorigin - WH_BOARD] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin - WH_BOARD, player, 0,depth);
        }
      }
    }
  }


   if (player == 0) // start at the end of the board
  {
    if (lastmove == 0)
    {
      if (!evaluateBoard(node)) // je sais pas comment mettre un nombre d'itération max
      {
        if (isValidPosition(node, posorigin + WH_BOARD, 1))
        {
          node->board[posorigin + WH_BOARD] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin + WH_BOARD, player, 0,depth);
        }
        if (isValidPosition(node, posorigin + 2, 1))
        {
          node->board[posorigin + 2] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin + 2, player, 1,depth);
        }

        if (isValidPosition(node, posorigin - 2, 1))
        {
          node->board[posorigin - 2] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin - 2, player, 2,depth);
        }

        // aller en arriere
        if (isValidPosition(node, posorigin - WH_BOARD, 1))
        {
          node->board[posorigin - WH_BOARD] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin - WH_BOARD, player, 3,depth);
        }
      }
    }

    if (lastmove == 1)
    {
      if (!evaluateBoard(node)) // je sais pas comment mettre un nombre d'itération max
      {
        int a = (int)rand() % 2;
        if (isValidPosition(node, posorigin + WH_BOARD, 1))
        {
          node->board[posorigin + WH_BOARD] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin + WH_BOARD, player, 0,depth);
        }
        if (isValidPosition(node, posorigin + 2, 1))
        {
          node->board[posorigin + 2] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin + 2, player, 1,depth);
        }

        if (isValidPosition(node, posorigin - WH_BOARD, 1))
        {
          node->board[posorigin - WH_BOARD] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin - WH_BOARD, player, 3,depth);
        }

        // aller à droite == revenir sur nos pas
        if (isValidPosition(node, posorigin - 2, 1))
        {
          node->board[posorigin - 2] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin - 2, player, 2,depth);
        }
      }
    }

    if (lastmove == 2)
    {
      if (!evaluateBoard(node)) // je sais pas comment mettre un nombre d'itération max
      {
        int a = (int)rand() % 2;
        if (isValidPosition(node, posorigin + WH_BOARD, 1))
        {
          node->board[posorigin + WH_BOARD] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin + WH_BOARD, player, 0,depth);
        }

        if (isValidPosition(node, posorigin - WH_BOARD, 1))
        {
          node->board[posorigin - WH_BOARD] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin - WH_BOARD, player, 3,depth);
        }

        if (a == 1)
        {
          if (isValidPosition(node, posorigin - 2, 1))
          {
            node->board[posorigin - 2] = 1;
            node->board[posorigin] = 0;

            return isPathAvailable(node, posorigin - 2, player, 2,depth);
          }
        }
        else
        {
          if (isValidPosition(node, posorigin + 2, 1))
          {
            node->board[posorigin + 2] = 1;
            node->board[posorigin] = 0;

            return isPathAvailable(node, posorigin + 2, player, 1,depth);
          }
        }
      }
    }

    if (lastmove == 3)
    {
      if (!evaluateBoard(node)) // je sais pas comment mettre un nombre d'itération max
      {
        // un peu de rand pour faire genre c'est une ia
        int a = (int)rand() % 2;
        if (a == 1)
        {
          if (isValidPosition(node, posorigin - 2, 1))
          {
            node->board[posorigin - 2] = 1;
            node->board[posorigin] = 0;

            return isPathAvailable(node, posorigin - 2, player, 2,depth);
          }
        }
        else
        {
          if (isValidPosition(node, posorigin + 2, 1))
          {
            node->board[posorigin + 2] = 1;
            node->board[posorigin] = 0;

            return isPathAvailable(node, posorigin + 2, player, 1,depth);
          }
        }

        // pas envie de passer notre temps à aller derriere
        if (isValidPosition(node, posorigin - WH_BOARD, 1))
        {
          node->board[posorigin - WH_BOARD] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin - WH_BOARD, player, 3,depth);
        }
        // aller tout droit = revenir sur nos pas
        if (isValidPosition(node, posorigin + WH_BOARD, 1))
        {
          node->board[posorigin + WH_BOARD] = 1;
          node->board[posorigin] = 0;

          return isPathAvailable(node, posorigin + WH_BOARD, player, 0,depth);
        }
      }
    }
  }
}

