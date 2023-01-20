#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>

#include "board.h"

#define NB_EMPLACEMENT_MUR (int)(WH_BOARD/2)
#define NB_CASE (int)(WH_BOARD/2)+1


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
  SDL_Init(SDL_INIT_VIDEO);
  // Créer la surface principale fenetre
  SDL_Surface *fenetre = NULL;
  fenetre = SDL_SetVideoMode(7*(50+5), 7*(50+5), 32, SDL_HWSURFACE); //NB_CASE*(50+5)

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

  murVertical = SDL_CreateRGBSurface(SDL_HWSURFACE, 5, 50, 32, 0, 0, 0, 0);
  SDL_FillRect(murVertical, NULL, couleurMur);

  murHorizontal = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 5, 32, 0, 0, 0, 0);
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
  

  for(int i = 0; i < NB_CASE; i++)
  {
    for (int j = 0; j < NB_CASE; j++)
    {
      SDL_Rect *rectCaseVide = initRect(i*55, j*55, 50, 50); //on crée un rectangle pour contenir la surface caseVide
      SDL_Rect *recMurVertical = initRect(i*(50+5)-5, j*(50+5), 50, 50); //on crée un rectangle pour contenir la surface caseVide
      SDL_Rect *recMurHorizontal = initRect(i*(50+5), (j-1)*(50+5)+50, 50, 50); //on crée un rectangle pour contenir la surface caseVide

      SDL_BlitSurface(caseVide, NULL, fenetre, rectCaseVide); //on copie la surface caseVide , ici définit a NULL, vers la fenêtre fenetre
      SDL_BlitSurface(murVertical, NULL, fenetre, recMurVertical); //on copie la surface caseVide , ici définit a NULL, vers la fenêtre fenetre
      SDL_BlitSurface(murHorizontal, NULL, fenetre, recMurHorizontal); //on copie la surface caseVide , ici définit a NULL, vers la fenêtre fenetre
    }
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
