#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

#include "player.h"
#include "item.h"
#include "board.h"

void movePlayer(Item *node, int player, int direction){

    if(player == 0){//correspond au joueur
        int tmp = node->player.pos; //garde l'ancienne position du joueur
        switch (direction)
        {
        case 0: //haut
            node->player.pos -= WH_BOARD; //on enlève WH_BOARD a la position dans la grille pour monter sur la ligne au dessus
            break;
        case 1: //droite
            node->player.pos += 2; //on ajoute 2 a la position dans la grille pour passer sur la case a droite
            break;
        case 2: // bas
            node->player.pos += WH_BOARD; //on ajoute WH_BOARD a la position dans la grille pour passer sur la ligne au dessous
            break;
        case 3: //gauche
            node->player.pos -= 2; //on retire 2 a la position dans la grille pour passer sur la case a gauche
            break;
        default:
            printf("Indiquez une valeur de déplacement comprise entre 0 et 3");
            break;
        }
        // change la position du joueur sur le board
        node->board[tmp] = 0;
        node->board[node->player.pos] = 1;

    }else if(player == 1){ //ia
        int tmp = node->ia.pos; //garde l'ancienne position de l'ia
        switch (direction)
        {
        case 0: //haut
            node->ia.pos -= WH_BOARD; //on enlève WH_BOARD a la position dans la grille pour monter sur la ligne au dessus
            break;
        case 1: //droite
            node->ia.pos += 2; //on ajoute 2 a la position dans la grille pour passer sur la case a droite
            break;
        case 2: // bas
            node->ia.pos += WH_BOARD; //on ajoute WH_BOARD a la position dans la grille pour passer sur la ligne au dessous
            break;
        case 3: //gauche
            node->ia.pos -= 2; //on retire 2 a la position dans la grille pour passer sur la case a gauche
            break;
        default:
            printf("Indiquez une valeur de déplacement comprise entre 0 et 3");
            break;
        }
        // change la position de l'ia sur le board
        node->board[tmp] = 0;
        node->board[node->ia.pos] = 2;
    } 
    
}


void putWall(Item *node, int position, int direction){
    
    assert(node->board[position] == -1);
    switch (direction)
    {
    case 0: //horizontal
        assert(node->board[position-1] == -1 && node->board[position+1] == -1 && node->board[position+2] == -1); // verifie que c'est un endroit pour murs
        node->board[position-1] = -2;
        node->board[position] = -2;
        node->board[position+1] = -2;
        node->board[position+2] = -2;
        break;
    case 1: //vertical
        assert(node->board[position-WH_BOARD] == -1 && node->board[position+WH_BOARD] == -1 && node->board[position+(2*WH_BOARD)] == -1); // verifie que c'est un endroit pour murs
        node->board[position-WH_BOARD] = -2;
        node->board[position] = -2;
        node->board[position+WH_BOARD] = -2;
        node->board[position+(2*WH_BOARD)] = -2;
        break;

    default:
        break;
    }
}
