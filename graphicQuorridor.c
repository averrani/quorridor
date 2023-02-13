#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include <SDL.h>

#include "board.h"
#include "player.h"

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

#define NB_EMPLACEMENT_MUR (int)(WH_BOARD/2)
#define NB_CASE (int)(WH_BOARD/2)+1



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


int minimaxAlphaBeta(Item *node, int depth, int alpha, int beta, int isMax){
  int i, bestScore;
  Item *child_p;
  if(evaluateBoard(node) != 0 || depth == 4){
    return evaluateBoard(node);
  }
    
  if(isMax){
     bestScore = -1000;
     for (i = 0; i < MAX_BOARD; i++){
        child_p = nodeAlloc();
        initBoard(child_p, node);
        child_p = getChildBoard(node, i );
        if (child_p != NULL) { // it's a valid child!
          bestScore = max(minimaxAlphaBeta(child_p, depth+1, alpha, beta, 0), bestScore);
          //elagage alpha beta 
          alpha = max( alpha, bestScore);
          if (beta <= alpha)
              break;
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
          bestScore = min(minimaxAlphaBeta(child_p, depth+1, alpha, beta, 1), bestScore);
          // elagage alpha beta
          beta = min(beta, bestScore);
          if (beta <= alpha)
             break;
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
        score = minimaxAlphaBeta(child_p, 1, -1000, 1000, 0);
        // score = minimax(child_p, 1, 0);
        if(score > bestScore){
          bestScore = score;
          bestMove = i;
          printf("Best pos : %d \n", bestMove);
        } 
    }
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



  while (1){
  if (node->player.pos >= 0 && node->player.pos < WH_BOARD){
    printf("Player win \n");
    return;
  }
  if (node->ia.pos >= WH_BOARD*(WH_BOARD+1) && node->ia.pos < MAX_BOARD)
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
      
      node->player.wall--;

      putWall(node, 0, positionWall);

      printBoard(node);
      switchPlayerTurn(node); // on change le trait, c'est au tour du joueur 2 de jouer
    }
  } 
  }
}

// void afficherGrille(SDL_Rect * case)
// {
//   case.x = 0;
//   case.y = 0;
//   SDL_BlitSurface(caseJoueur, NULL, fenetre, &caseVidePosition);

//   case.x = 55;
//   case.y = 0;
//   SDL_BlitSurface(caseJoueur, NULL, fenetre, &caseVidePosition);
// }


SDL_Rect *initRect(int XPos, int YPos, int Width, int Height)
{
SDL_Rect *Rect = malloc(sizeof(SDL_Rect)) ;
Rect->h = Height;
Rect->w = Width;
Rect->x = XPos;
Rect->y = YPos;

return Rect;
}


int main()
{
  int ii, jj;

  srand( time( NULL ) ); //tests ia

  /* init lists */

  Item *initial_state = initGame();
  // printBoard(initial_state);
  // gameActionLoop(initial_state);


  SDL_Init(SDL_INIT_VIDEO);
  // Créer la surface principale fenetre
  SDL_Surface *fenetre = NULL;
  fenetre = SDL_SetVideoMode(13*(50+5), 13*(50+5), 32, SDL_HWSURFACE); //NB_CASE*(50+5)

  // Créer et stocker des couleurs
  Uint32 couleurFenetre, couleurCaseVide, couleurCaseJoueur, couleurCaseIa, couleurMur;

  
  couleurFenetre = SDL_MapRGB(fenetre->format, 0, 0, 0);
  couleurCaseVide = SDL_MapRGB(fenetre->format, 255, 255, 255);
  couleurCaseJoueur = SDL_MapRGB(fenetre->format, 200, 70, 10);
  couleurCaseIa = SDL_MapRGB(fenetre->format, 60, 200, 10);
  couleurMur = SDL_MapRGB(fenetre->format, 60, 230, 230);

  SDL_FillRect(fenetre, NULL, couleurFenetre); //on remplii la fenetre de la couleur couleurFenetre
  SDL_Flip(fenetre); //on envoie dans la fenetre les modifications

  // Création des surfaces de jeu
  SDL_Surface *caseVide;
  SDL_Surface *caseJoueur;
  SDL_Surface *caseIa;
  SDL_Surface *murVertical;
  SDL_Surface *murHorizontal;

  caseVide = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 50, 32, 0, 0, 0, 0);
  SDL_FillRect(caseVide, NULL, couleurCaseVide);

  caseJoueur = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 50, 32, 0, 0, 0, 0);
  SDL_FillRect(caseJoueur, NULL, couleurCaseJoueur);

  caseIa = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 50, 32, 0, 0, 0, 0);
  SDL_FillRect(caseIa, NULL, couleurCaseIa);

  murVertical = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 50, 32, 0, 0, 0, 0);
  SDL_FillRect(murVertical, NULL, couleurMur);

  murHorizontal = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 50, 32, 0, 0, 0, 0);
  SDL_FillRect(murHorizontal, NULL, couleurMur);


//Création des rectangles de jeu contenant les surfaces de jeu
  // SDL_Rect *rectCaseVide = initRect(0, 0, 50, 50); //on crée un rectangle pour contenir la surface caseVide
  // SDL_BlitSurface(caseVide, NULL, fenetre, rectCaseVide); //on copie la surface caseVide , ici définit a NULL, vers la fenêtre fenetre
  // //Ici le premier NULL correspond au rectangle contenant la surface a copier, le second représente le rectangle dans laquelle la copie est effectuée

  // SDL_Rect *rectCaseJoueur = initRect(50, 0, 50, 50); //on crée un rectangle pour contenir la surface caseVide
  // SDL_BlitSurface(caseJoueur, NULL, fenetre, rectCaseJoueur); //on copie la surface caseVide , ici définit a NULL, vers la fenêtre fenetre

  // SDL_Rect *rectCaseIa = initRect(100, 0, 50, 50); //on crée un rectangle pour contenir la surface caseVide
  // SDL_BlitSurface(caseIa, NULL, fenetre, rectCaseIa); //on copie la surface caseVide , ici définit a NULL, vers la fenêtre fenetre

  // SDL_Rect *recMurVertical = initRect(150, 0, 50, 50); //on crée un rectangle pour contenir la surface caseVide
  // SDL_BlitSurface(murVertical, NULL, fenetre, recMurVertical); //on copie la surface caseVide , ici définit a NULL, vers la fenêtre fenetre

  // SDL_Rect *recMurHorizontal = initRect(150, 0, 50, 50); //on crée un rectangle pour contenir la surface caseVide
  // SDL_BlitSurface(murHorizontal, NULL, fenetre, recMurHorizontal); //on copie la surface caseVide , ici définit a NULL, vers la fenêtre fenetre
  

  for(int i = 0; i < MAX_BOARD; i++)
  {

    ii = i / WH_BOARD;
    jj = i % WH_BOARD;

      if((initial_state->board[i] == -2) && (i%2 == 0))
      {
        SDL_Rect *recMurVertical = initRect(ii*55, jj*55, 50, 50); //on crée un rectangle pour contenir la surface caseVide
        SDL_BlitSurface(murVertical, NULL, fenetre, recMurVertical); //on copie la surface caseVide , ici définit a NULL, vers la fenêtre fenetre
      }
      
      if((initial_state->board[i] == -2) && (i%2 == 1))
      {
        SDL_Rect *recMurHorizontal = initRect(ii*55, jj*55, 50, 50); //on crée un rectangle pour contenir la surface caseVide
        SDL_BlitSurface(murHorizontal, NULL, fenetre, recMurHorizontal); //on copie la surface caseVide , ici définit a NULL, vers la fenêtre fenetre
      }

      if(initial_state->board[i] == 0)
      {
        SDL_Rect *rectCaseVide = initRect(ii*55, jj*55, 50, 50); //on crée un rectangle pour contenir la surface caseVide
        SDL_BlitSurface(caseVide, NULL, fenetre, rectCaseVide); //on copie la surface caseVide , ici définit a NULL, vers la fenêtre fenetre
      }

      if(initial_state->board[i] == 1)
      {
        SDL_Rect *recJoueur = initRect(ii*55, jj*(55), 50, 50); //on crée un rectangle pour contenir la surface joueur
        SDL_BlitSurface(caseJoueur, NULL, fenetre, recJoueur); //on copie la surface caseVide , ici définit a NULL, vers la fenêtre fenetre
      }

      if(initial_state->board[i] == 2)
      {
        SDL_Rect *recIa = initRect(ii*55, jj*55, 50, 50); //on crée un rectangle pour contenir la surface joueur
        SDL_BlitSurface(caseIa, NULL, fenetre, recIa); //on copie la surface caseVide , ici définit a NULL, vers la fenêtre fenetre
      }

      // if(initial_state->player.pos == ((i*NB_CASE)+j))
      // {
      //   SDL_Rect *recJoueur = initRect(i*(50+5), (j-1)*(50+5)+50, 50, 50); //on crée un rectangle pour contenir la surface joueur
      //   SDL_BlitSurface(caseJoueur, NULL, fenetre, recJoueur); //on copie la surface caseVide , ici définit a NULL, vers la fenêtre fenetre
      // }

      // if(initial_state->ia.pos == ((i*NB_CASE+j)))
      // {
      //   SDL_Rect *recIa = initRect(i*(50+5), (j-1)*(50+5)+50, 50, 50); //on crée un rectangle pour contenir la surface ia
      //   SDL_BlitSurface(caseIa, NULL, fenetre, recIa); //on copie la surface caseVide , ici définit a NULL, vers la fenêtre fenetre
      // }


  }

  //Puis on envoie dans la fenetre le résultat
  SDL_Flip(fenetre); 

  while (1)
  {
    SDL_Event event;
    SDL_WaitEvent(&event);
    if (event.type == SDL_QUIT)
    {
      break;
    }
  }

  // Liberer la mémoire
  SDL_FreeSurface(fenetre);
  SDL_Quit();

  return 0;
}
