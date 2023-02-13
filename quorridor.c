#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// #include <malloc.h>

#include "board.h"
#include "player.h" // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ENLEVER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

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


int randIA(Item *node){
  int p = rand() % MAX_BOARD;

  if (isValidPosition(node, p, 1))
      moveIA(node, p, 0);
  else if(isValidPositionWall(node, p))
      putWall(node, 1, p);
  else
      randIA(node);
  switchPlayerTurn(node);
}

// Minimax Tentative 2 |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||-

// int minimax(Item *node, int depth, int isMax){
//   int i, bestScore;
//   Item *child_p;
//   if(evaluateBoard(node) != 0){
//     return evaluateBoard(node);
//   }
    
//   if(isMax){
//      bestScore = -1000;
//      for (i = 0; i < MAX_BOARD; i++){
//         child_p = nodeAlloc();
//         initBoard(child_p, node);
//         child_p = getChildBoard(node, i );
//         if (child_p != NULL) { // it's a valid child!
//           bestScore = max(minimax(child_p, depth+1, 0), bestScore);
//         }
//       }
//       return bestScore;
//     }else {
//       bestScore = 1000;
//       for (i = 0; i < MAX_BOARD; i++){
//         child_p = nodeAlloc();
//         initBoard(child_p, node);
//         child_p = getChildBoardPlayer(node, i);
//         if (child_p != NULL) { // it's a valid child!
//           bestScore = min(minimax(child_p, depth+1, 1), bestScore);
//         }
//       }
//       return bestScore;
//     }
// }

int p= 0;
int minimaxAlphaBeta(Item *node, int depth, int alpha, int beta, int isMax){
  int i, bestScore;
  Item *child_p;
  if(evaluateBoard(node) != 0 || depth == 5){
    return evaluateBoard(node);
  }
    
  if(isMax){
     bestScore = -1000;
     for (i = 0; i < MAX_BOARD; i++){
        
        child_p = getChildBoard(node, i );
        p++;
        if (child_p != NULL) { // it's a valid child!
          bestScore = max(minimaxAlphaBeta(child_p, depth+1, alpha, beta, 0), bestScore);
          //freeItem(node);
          //elagage alpha beta 
          alpha = max( alpha, bestScore);
          if (beta <= alpha)
              break;
        }
        //freeItem(node);
      }
      return bestScore;
    }else {
      bestScore = 1000;
      for (i = 0; i < MAX_BOARD; i++){

        child_p = getChildBoardPlayer(node, i);
        p++;
        
        if (child_p != NULL) { // it's a valid child!
          bestScore = min(minimaxAlphaBeta(child_p, depth+1, alpha, beta, 1), bestScore);
          //freeItem(node);
          // elagage alpha beta
          beta = min(beta, bestScore);
          if (beta <= alpha)
             break;
        }
        //freeItem(node);
      }
      return bestScore;
    }
}


int bestMoveIA(Item *node){
  Item *child_p;
  int bestScore = -1000;
  int bestMove;
  int score;

  /* Copy first struct values into the second one */
  for (int i = 0; i < MAX_BOARD; i++){
      child_p = getChildBoard(node, i );
      p++;
      if (child_p != NULL) { // it's a valid child!
        score = minimaxAlphaBeta(child_p, 1, -1000, 1000, 0);
        //freeItem(node);
        // score = minimax(child_p, 1, 0);
        if(score > bestScore){
          bestScore = score;
          bestMove = i;
          printf("Best pos : %d \n", bestMove);
        } 
    }
    //freeItem(node);
  }
  if(isValidPosition(node, bestMove, 1))
    moveIA(node, bestMove, 0);
  else if(isValidPositionWall(node, bestMove)){
    putWall(node, 1, bestMove);
    node->ia.wall--;
  }
  
  node->turn = 0; 
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
  if (node->player.pos >= 0 && node->player.pos < WH_BOARD){
    printf("Player win \n");
    return;
  }
  if (node->ia.pos >= WH_BOARD*(WH_BOARD-1) && node->ia.pos < MAX_BOARD)
  {
    printf("ia win \n");
    return;
  } 
  // if(evaluateBoard(node) == 1.0){
  //   return;
  // }
  if(node->turn == 1){ // a l'ia de jouer 
    bestMoveIA(node);
    printBoard(node);
    printf("%d\n", p);
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

      movePlayer(node, directionMove);

      printBoard(node);       // on affiche la grille après les modifications

      
      switchPlayerTurn(node); // on change le trait, c'est au tour du joueur 2 de jouer
    }

  else if (actionMove == 1) // si action == 1, on pose un mur
    {
        printf("Action = 1\n");

      setPositionWall(&positionWall);
      printf("positionWall : %d\n", positionWall);
      
      node->player.wall --;

      putWall(node, 0, positionWall);

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
  Item *initial_state = initGame();
  printBoard(initial_state);

  // movePlayer(initial_state, 1, 2);
  // printBoard( initial_state );

  // int i;
  // for(i =0; i<MAX_BOARD; i++){
  //   printf("%d %d \n",i, isValidPosition(initial_state, i, 1));
  // }
  // for(i =0; i<MAX_BOARD; i++){
  //   if(isValidPositionWall(initial_state, i))
  //     putWall(initial_state,0,i);
  // }
  // printBoard(initial_state);

  gameActionLoop(initial_state);

  // addLast(&openList_p, initial_state);
  // // printList(openList_p);

  // // minimax();


  return 0;
}