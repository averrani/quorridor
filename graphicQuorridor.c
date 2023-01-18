#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include <SDL.h>
#include <SDL2/SDL_image.h>

void initVideoSDL()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    SDL_Log("Erreur : Initialisation SDL > %s \n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

SDL_Window *createWindow()
{
  SDL_Window *window = SDL_CreateWindow("Quorridor | IA&Jeux",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            800,
                            600,
                            0);

  return window;
}

void checkWindowCreated(SDL_Window *window)
{
  if(window == NULL)
  {
    SDL_Log("ERREUR : Création fenêtre échouée > %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

int main()
{
  SDL_Window *window = NULL;

  

  initVideoSDL();

  SDL_Surface* image = IMG_Load("data/case.png");
if(!image)
{
    printf("Erreur de chargement de l'image : %s",SDL_GetError());
    return -1;
}

  window = createWindow();
  checkWindowCreated(window);

  SDL_Delay(5000);

  SDL_Quit();

  return EXIT_SUCCESS; //return 0
}