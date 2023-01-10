#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

#include "player.h"

void movePlayer(Player player, int direction){
    switch (direction)
    {
    case 0:
        player.pos -= 17; //on enlève 17 a la position dans la grille pour monter sur la ligne au dessus
        break;
    case 1:
        player.pos += 2; //on ajoute 2 a la position dans la grille pour passer sur la case a droite
        break;
    case 2:
        player.pos += 17; //on ajoute 17 a la position dans la grille pour monter sur la ligne au dessus
        break;
    case 3:
        player.pos -= 2; //on retire 2 a la position dans la grille pour passer sur la case a gauche
        break;
    default:
        printf("Indiquez une valeur de déplacement comprise entre 0 et 3");
        break;
    }
}


void putWall(int position, int direction){
    // switch (direction)
    // {
    // case /* constant-expression */:
    //     /* code */
    //     break;
    
    // default:
    //     break;
    // }
}
