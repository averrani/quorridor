#include "Player.h"

void makeMove(Item *node, int pos)
{
  if (isValidPosition(node, pos))
  { // tester d'abord si la position pos est valide
    if (node->player1.turn == 1)
    { // Verifier si c'est le tour du joueur1
      node->player1.pos = pos;
    }
    else
    {
      node->player2.pos = pos;
    }
  }
}

void putStick(Item *node, int pos)
{ // placer un mur "Stick"
  if (node->board[pos] == -1)
  { // verifier si on peut placer un mur à la position pos
    if ((node->player1.turn == 1) || (node->player1.wall != 0))
    {
      /*placer un mur */
      /* To do */

      node->player1.wall--; // diminuer le nombre de murs du joueur
    }
    else if ((node->player2.turn == 1) || (node->player2.wall != 0))
    {
      /* code */

      node->player2.wall--;
    }
  }
}