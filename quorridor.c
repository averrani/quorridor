#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// #include <malloc.h>

#include "list.h"
#include "board.h"
#include "player.h" // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ENLEVER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

list_t openList_p;
list_t closedList_p;

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
  int p = rand() % MAX_BOARD;

  if (isValidPosition(node, p, 1))
      moveIA(node, p, 0);
  else if(isValidPositionWall(node, p))
      putWall(node, 1, p);
  else
      randIA(node);
  switchPlayerTurn(node);
}

// Minimax 4 eme tentative !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ntm!!!!!!!!!!!!!!!!!!!!!!!!!!
// int bestMove;

// int minimax(Item *node, int depth, int isMax)
// {
//   Item *child;
//     if (depth == 0 || evaluateBoard(node) != 0) {
//         return evaluateBoard(node);
//     }

//     if (isMax) { // modifier avec player turn et mettre a 0 et 1 manuellement, pas d'appel a switch
//         int bestScore = -100;
//         for (int i = 0; i < MAX_BOARD; i++){
//           child = getChildBoard(node, i );
//           if (child != NULL) { // it's a valid child!
//             int score = minimax(child, depth+1, 0);
//             if (score > bestScore) {
//                 bestScore = score;
//                 bestMove = i;
//             }
//             }
//         }
//     } else {
//         int bestScore = 100;
//         for (int i = 0; i < MAX_BOARD; i++){
//           child = getChildBoardPlayer(node, i );
//           if (child != NULL) { // it's a valid child!
//             int score = minimax(child, depth - 1, 1);
//             if (score < bestScore) {
//                 bestScore = score;
//                 bestMove = i;
//             }
//         }
//         }
//         return bestScore;
//     }
// }

// int bestMoveIA(Item *node){
//   minimax(node, 2, 1);

//   if(isValidPosition(node, bestMove, 1))
//     moveIA(node, bestMove, 0);
//   else if(isValidPositionWall(node, bestMove))
//     putWall(node, 1, bestMove);
  
//   node->turn = 0; 
// }


// Minimax Tentative 1 |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||-

// int bestMovePlayable; // coup optimal pour l'ia

// int minimaxAlphaBeta(Item * node ,int depth , int alpha , int beta){
//   Item *child;
//   if(depth == 0 || evaluateBoard(node)!= 0){
//     return evaluateBoard(node) ; // à faire 
//   }
//   if(node->turn == 1 ){ // c'est l'ia qui joue donc max 
//      for (int i = 0; i < MAX_BOARD; i++){
//         child = getChildBoard(node, i );
//         if (child != NULL) { // it's a valid child!
//             node->turn == 0;
//             alpha = max(alpha,minimaxAlphaBeta(child,depth-1,alpha,beta));
//             if(beta <= alpha){
//               break;
//             }
//           }
//      }
//       return alpha;
//   }
//   else{
//     for (int i = 0; i < MAX_BOARD; i++){
//         child = getChildBoardPlayer(node, i );
//         if (child != NULL) { // it's a valid child!
//           node->turn == 1;
//           alpha = min(alpha,minimaxAlphaBeta(child,depth-1,alpha,beta));
//           if(beta <= alpha){
//             break;
//           }
//         }
//      }
//      return beta;
//   }
// }

// int minmaxWithMov(Item * node ,int depth , int alpha , int beta){
//   Item *child;
//     if (evaluateBoard(node)!=0 || depth == 0){
//       return evaluateBoard(node) ; // a refaire
//     }
//     if(node->turn == 1){
//       int val;
//       for (int i = 0; i < MAX_BOARD; i++){
//         child = getChildBoard(node, i );
//         if (child != NULL) { // it's a valid child!
//           node->turn == 0;
//           val = minimaxAlphaBeta(child,depth-1,alpha,beta);
//           if(val>alpha){
//             alpha = val;
//             bestMovePlayable = i;
//           }
//           if(beta<= alpha){
//             break;
//           }
//         }
//     }
//     return alpha;
// }
// else{
//   for (int i = 0; i < MAX_BOARD; i++){
//       child = getChildBoardPlayer(node, i );
//         if (child != NULL) { // it's a valid child!
//           node->turn == 1;
//           beta =min(beta,minimaxAlphaBeta(child,depth-1,alpha,beta));
//           if(beta<= alpha){
//             break;
//           }
//         }
//   }
//   return beta;
// }
// }

// int bestMoveIA(Item *node){
//   Item *child_p= nodeAlloc();
//   int bestScore = -1000;
//   int bestMove;
//   int score;

//   /* Copy first struct values into the second one */
//   initBoard(child_p, node);

//   for (int i = 0; i < MAX_BOARD; i++){
//         score = minmaxWithMov(child_p, 5, -1000, 1000);
//         if(score > bestScore){
//           bestScore = score;
//           bestMovePlayable = i;
//         }
//   }
//   if(isValidPosition(node, bestMovePlayable, 1)){
//     moveIA(node, bestMovePlayable, 0);
//   }
//   else if(isValidPositionWall(node, bestMovePlayable))
//     putWall(node, 1, bestMovePlayable);
//   printf("%d\n", bestScore);

//   node->turn = 0; 
// }


// Minimax Tentative 3 |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||-

// int minimax(Item *node, int depth, int isMax){
//   int i, bestScore, tmp_pos;
//   Item *copy =nodeAlloc();
//   int score = evaluateBoard(node);
//   if(score == 10 || score == -10 || depth == 10){
//     return score;
//   }
    
//   if(isMax){
//      bestScore = -1000;
//      for (i = 0; i < MAX_BOARD; i++){
//         if(isValidPosition(node, i, 1) || isValidPositionWall(node, i)){ //teste si la position correspond a un move
  
//           if(isValidPosition(node, i, 1)){
//             initBoard(copy->board,node);
//             moveIA(node, i, 0); //make move
//             score = minimax(node, depth+1, 0);
//             initBoard(node->board,copy); //undo move
//             bestScore = max(score, bestScore);
//           }
            
//           else if(isValidPositionWall(node, i)){
//             initBoard(copy->board,node);
//             putWall(node,1, i);
//             score = minimax(node, depth+1, 0);
//             initBoard(node->board,copy);
//             bestScore = max(score, bestScore);
//           }
//         }
//       }
//       return bestScore;
//     }else {
//       bestScore = 1000;
//       for (i = 0; i < MAX_BOARD; i++){
//           if(isValidPosition(node, i, 0) || isValidPositionWall(node, 0)){ //teste si la position correspond a un move
  
//             if(isValidPosition(node, i, 0)){
//               initBoard(copy->board,node);
//               moveIA(node, i, 1); //make move
//               score = minimax(node, depth+1, 1);
//               initBoard(node->board,copy); //undo move
//               bestScore = min(score, bestScore);
//             }
              
//             else if(isValidPositionWall(node, i)){
//               initBoard(copy->board,node);
//               putWall(node,0, i);
//               score = minimax(node, depth+1, 1);
//               initBoard(node->board,copy);
//               bestScore = min(score, bestScore);
//             }
//           }
//       }
//       return bestScore;
//     } 
// }

// int bestMove(Item *node){
//   Item *copy = nodeAlloc();
//   int bestScore = -1000;
//   int bestMove, tmp_pos;
//   int score;
//   for (int i = 0; i < MAX_BOARD; i++){
//       if(isValidPosition(node, i, 1) || isValidPositionWall(node, i)){ //teste si la position correspond a un move
  
//           if(isValidPosition(node, i, 1)){
//             initBoard(copy->board,node);
//             moveIA(node, i, 0); //make move
//             score = minimax(node, 1, 0);
//             initBoard(node->board,copy); //undo move
//             if(score > bestScore){
//               bestScore = score;
//               bestMove = i;
//             } 
//           }
            
//           else if(isValidPositionWall(node, i)){
//             initBoard(copy->board,node);
//             //printBoard(node);
//             putWall(node,1, i);
//             score = minimax(node, 1, 0);
//             initBoard(node->board,copy);
//             if(score > bestScore){
//               bestScore = score;
//               bestMove = i;
//             } 
//           }
//       }        
//     }
//   if(isValidPosition(node, bestMove, 1))
//     moveIA(node, bestMove, 0);
//   else if(isValidPositionWall(node, bestMove))
//     putWall(node, 1, bestMove);
  
//   switchPlayerTurn(node); 
// }

// Minimax Tentative 2 |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||-

int minimax(Item *node, int depth, int isMax){
  int i, bestScore;
  Item *child_p;
  if(evaluateBoard(node) != 0 || depth == 3){
    return evaluateBoard(node);
  }
    
  if(isMax){
     bestScore = -1000;
     for (i = 0; i < MAX_BOARD; i++){
        child_p = nodeAlloc();
        initBoard(child_p, node);
        child_p = getChildBoard(node, i );
        if (child_p != NULL) { // it's a valid child!
          bestScore = max(minimax(child_p, depth+1, 0), bestScore);
        }
      }
      return bestScore;
    }else {
      bestScore = 1000;
      for (i = 0; i < MAX_BOARD; i++){
        child_p = nodeAlloc();
        initBoard(child_p, node);
        child_p = getChildBoardPlayer(node, i);
        if (child_p != NULL) { // it's a valid child!
          bestScore = min(minimax(child_p, depth+1, 1), bestScore);
        }
      }
      return bestScore;
    }
}


int bestMoveIA(Item *node){
  Item *child_p = nodeAlloc();
  int bestScore = -1000;
  int bestMove;
  int score;

  /* Copy first struct values into the second one */
  initBoard(child_p,node);
  for (int i = 0; i < MAX_BOARD; i++){
      child_p = nodeAlloc();
      initBoard(child_p, node);
      child_p = getChildBoard(child_p, i );
      if (child_p != NULL) { // it's a valid child!
        score = minimax(child_p, 0, 0);
        if(score > bestScore){
          bestScore = score;
          bestMove = i;
        } 
    }
  }
  if(isValidPosition(node, bestMove, 1))
    moveIA(node, bestMove, 0);
  else if(isValidPositionWall(node, bestMove))
    putWall(node, 1, bestMove);
  
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
    printf("Player win");
    return;
  }
  if (node->ia.pos >= WH_BOARD*(WH_BOARD+1) && node->ia.pos < MAX_BOARD)
  {
    printf("ia win");
    return;
  } 
  // if(evaluateBoard(node) == 1.0){
  //   return;
  // }
  if(node->turn == 1){ // a l'ia de jouer 
    bestMoveIA(node);
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

  printf("Finished!\n");

  /* clean lists */
  cleanupList(&openList_p);
  cleanupList(&closedList_p);

  return 0;
}