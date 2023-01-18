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


int randIA(Item *node){
  int i = rand() % 2; 
  int d,p;
  if(i == 0){
    d = rand() % 4; 
    switch (d)
        {
        case 0: //haut
            if(isValidPosition(node,node->ia.pos -(2*WH_BOARD),1))
              movePlayer(node, 1, d);
            else randIA(node);
            break;
        case 1: //droite
            if(isValidPosition(node,node->ia.pos + 2,1))
              movePlayer(node, 1, d);
            else randIA(node);
            break;
        case 2: //bas
            if(isValidPosition(node,node->ia.pos + (2*WH_BOARD),1))
              movePlayer(node, 1, d);
            else randIA(node);
            break;
        case 3: //gauche
            if(isValidPosition(node,node->ia.pos - 2,1))
              movePlayer(node, 1, d);
            else randIA(node);
            break;
        }
    
  }else{
    p = rand() % MAX_BOARD;
    d = rand() % 1;
    if(isValidPositionWall(node, p, d))
      putWall(node, 1, p, d);
    else randIA(node);
  }
  // int value;
  // Item *cur_node = popFirst(&openList_p);
  // if(cur_node->depth == 0)
  //   return cur_node->g; //heuristic
  // if(isMax){
  //   value = -100000;
  //   value = max(value, minimax(getChildBoard(cur_node, i)))
  // }

  switchPlayerTurn(node);
}


void switchPlayerTurn(Item *node) // fonction permettant de changer le trait de la partie
{
  if (node->turn == 0)
    node->turn = 1;
  else if (node->turn == 1)
    node->turn = 0;
}

void getTurnPlayer(Item *node) // fonction indiquant qui possède le trait
{
  if (node->turn == 0)
    printf("C'est à l'humain de jouer \n");
  else
    printf("C'est à l'ia de jouer\n");
}

void setAction(int *action) // fonction gérant le choix de l'utilisateur sur l'action à effectuer
{
  printf("Donnez une action a effectuer : 0 => Déplacer Joueur | 1 => Poser Mur \n");
  scanf("%d", action);
}

void setDirectionMove(int *directionMove)
{
  printf("Donnez une direction de déplacement : 0-1-2-3 => Haut | Droite | Bas | Gauche \n");
  scanf("%d", directionMove);
}

void setPositionWall(int *positionWall)
{
  printf("Donnez la position du mur à placer : \n");
  scanf("%d", positionWall);
}

void setDirectionWall(int *directionWall)
{
  printf("Donnez la direction du mur à placer : \n");
  scanf("%d", directionWall);
}

void gameActionLoop(Item *node)
{
  int actionMove;    // si action == 0, on deplace le pion, si action == 1, on place un mur
  int directionMove; // Indique le sens de déplacement du joueur 0-1-2-3 : haut-droite-bas-gauche
  int positionWall;  // indique la position du mur à placer
  int directionWall; // indique la direction du mur à placer



  //dans la fonction de set Action, on demande d'indiquer une fois la valeur de action, 
  //puis on doit indiquer une deuxième valeur qui n'est pas action...
  //cette deuxième valeur à indiquer est en fait la valeur de directionMove ou positionWall 
  //selon la valeur de action

  while (1){

  if(evaluateBoard(node) == 1.0){
    return;
  }
  if(node->turn == 1){ // a l'ia de jouer 
    randIA(node);
    printBoard(node);
  }else{
  
    setAction(&actionMove);
    printf("action : %d\n", actionMove);

  if (actionMove == 0) // si action == 0, on effectue le déplacement du pion
    {
      setDirectionMove(&directionMove); // directionMov NE S'ENREGISTRE PAS
      printf("directionMove : %d\n", directionMove);

      // on vérifie que le directionMove est une valeur exploitable
      assert(directionMove > -1);
      assert(directionMove < 4);

      movePlayer(node, 0, directionMove);

      printBoard(node);       // on affiche la grille après les modifications
      switchPlayerTurn(node); // on change le trait, c'est au tour du joueur 2 de jouer
    }

  else if (actionMove == 1) // si action == 1, on pose un mur
    {
        printf("Action = 1\n");

      setPositionWall(&positionWall);
      printf("positionWall : %d\n", positionWall);

      setDirectionWall(&directionWall);
      printf("directionWall : %d\n", directionWall);

      putWall(node, 0, positionWall, directionWall);

      printBoard(node);
      switchPlayerTurn(node); // on change le trait, c'est au tour du joueur 2 de jouer
    }
  } 
  }
}

int main()
{

  srand( time( NULL ) ); //tests ia

  /* init lists */
  initList(&openList_p);
  initList(&closedList_p);

  printf("\nInitial:");
  Item *initial_state = initGame();
  printBoard(initial_state);

  printf("\nSearching ...\n");

  // movePlayer(initial_state, 1, 2);
  // printBoard( initial_state );

  // int i;
  // for(i =0; i<MAX_BOARD; i++){
  //   //printf("%d %d \n",i, isValidPositionWall(initial_state, i, 1));
  // }
  // for(i =0; i<MAX_BOARD; i++){
  //   if(isValidPositionWall(initial_state, i, 1))
  //     putWall(initial_state,0,i,1);
  // }
  // printBoard(initial_state);

  gameActionLoop(initial_state);

  // addLast(&openList_p, initial_state);
  // // printList(openList_p);

  // // minimax();

  printf("Finished!\n");

  /* clean lists */
  cleanupList(&openList_p);
  cleanupList(&closedList_p);

  return 0;
}