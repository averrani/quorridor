#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
// #include <malloc.h>

#include "list.h"
#include "board.h"
#include "player.h" // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ENLEVER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

list_t openList_p;
list_t closedList_p;

void showSolution(Item *goal)
{
  int i = 0, j;

  printf("\nSolution:");

  while (goal)
  {
    printBoard(goal);
    goal = goal->parent;
    i++;
  }

  printf("\nLength of the solution = %d\n", i - 1);
  printf("i");
  printf("Size of open list = %d\n", openList_p.numElements);
  printf("Size of closed list = %d\n", closedList_p.numElements);
  return;
}

/*
int minimax(int isMax){
  int value;
  Item *cur_node = popFirst(&openList_p);
  if(cur_node->depth == 0)
    return cur_node->g; //heuristic

  if(isMax){
    value = -100000;
    value = max(value, minimax(getChildBoard(cur_node, i)))

  }
}
*/

//fonction permettant de changer le trait de la partie
void switchPlayerTurn(int player)
{
  if(player == 0)player = 1;
  if(player == 1)player = 0;
}

void gameActionLoop(Item *node)
{
  int player = 0; // indique le trait, si player = 0, c'est au joueur 1 de jouer, joueur 2 sinon

  int directionMove; // Indique le sens de déplacement du joueur 1-2-3-4 : haut-droite-bas-gauche

  int action; // si action == 0, on deplace le pion, si action == 1, on met place un mur

  int directionWall, positionWall; // indique la direction et la position du mur a placer
  while (1)                // tant que l'utilisateur n'a pas choisit de quitter le jeu (exit == 1)
  {
      printf("Donnez une action a effectuer : 0 => Déplacer Joueur | 1 => Poser Mur \n");
      scanf("%d\n", &action);
      printf("action : %d\n", action);

      if(action == 0)
      {
        // si action == 0, on effectue le déplacement du pion
        printf("Donnez une direction de déplacement : 0-1-2-3 => haut-droite-bas-gauche\n");
        scanf("%d\n", &directionMove);
        printf("directionMove : %d\n", directionMove);


        // on vérifie que le directionMove est une valeur exploitable
        assert(directionMove > -1);
        assert(directionMove < 4);

        movePlayer(node, player, directionMove);

        printBoard(node);//on affiche la grille après les modifications
        switchPlayerTurn(player); //on change le trait, c'est au tour du joueur 2 de jouer
      }
      else if(action == 1)// si action == 1, on pose un mur
      {
        printf("Donnez une position pour le mur\n");
        scanf("%d\n", &positionWall);
        printf("positionWall : %d\n", positionWall);
        

        printf("Donnez une direction/orientation pour le mur : 0 => horizontal | 1 => vertical\n");
        scanf("%d\n", &directionWall);
        printf("directionWall : %d\n", directionWall);


        putWall(node, positionWall, directionWall);

        printBoard(node);
        switchPlayerTurn(player); // on change le trait, c'est au tour du joueur 2 de jouer

      }
  }
}

int main()
{
  printf("\n"); // segmentation error without this line ???
  /* init lists */
  initList(&openList_p);
  initList(&closedList_p);

  printf("\nInitial:");
  Item *initial_state = initGame();
  // printBoard( initial_state );

  printf("\nSearching ...\n");

  // movePlayer(initial_state, 0, 0);
  // putWall(initial_state, 14, 0);
  // putWall(initial_state, 10, 0);
  // printBoard(initial_state);
  // printf("%d \n", isValidPosition(initial_state, 2, 0));

  gameActionLoop(initial_state);

  addLast(&openList_p, initial_state);
  // printList(openList_p);

  // minimax();

  printf("Finished!\n");

  /* clean lists */
  cleanupList(&openList_p);
  cleanupList(&closedList_p);

  return 0;
}
