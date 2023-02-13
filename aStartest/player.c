#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

#include "player.h"
#include "item.h"
#include "board.h"

// player == 0 pour joueur
// player == 1 pour ia
void movePlayer(Item *node, int player, int direction)
{

    if (player == 0)
    { // correspond au joueur

        int tmp = node->player.pos; // garde l'ancienne position du joueur
        switch (direction)
        {
        case 0: // haut
            if (isValidPosition(node, node->player.pos - 2 * WH_BOARD, 0))
            {
                if (node->player.pos - 2 * WH_BOARD == node->ia.pos)
                { // on ajoute l'exception si la position ou le joueur veut aller est celle de l'ia
                    if ((node->player.pos - 4 * WH_BOARD) % WH_BOARD == node->player.pos % WH_BOARD)
                    {                                     // exception pour pas sortir du board en cas de jump
                        node->player.pos -= 4 * WH_BOARD; // jump
                    }
                    else
                        printf("deplacement impossible exception sortie board \n");
                }
                else
                    node->player.pos -= 2 * WH_BOARD; // on enlève WH_BOARD a la position dans la grille pour monter sur la ligne au dessus
            }
            else
                printf("Sortie de board");
            break;
        case 1: // droite
            if (isValidPosition(node, node->player.pos + 2, 0))
            {
                if (node->player.pos + 2 == node->ia.pos)
                {
                    if ((node->player.pos + 4) / WH_BOARD == node->player.pos / WH_BOARD)
                    {
                        node->player.pos += 4;
                    }
                    else
                        printf("deplacement impossible exception sortie board \n");
                }
                else
                    node->player.pos += 2; // on ajoute 2 a la position dans la grille pour passer sur la case a droite
            }
            else
                printf("Sortie de board");
            break;
        case 2: // bas
            if (isValidPosition(node, node->player.pos + 2 * WH_BOARD, 0))
            {
                if (node->player.pos + 2 * WH_BOARD == node->ia.pos)
                {
                    if ((node->player.pos + 4 * WH_BOARD) % WH_BOARD == node->player.pos % WH_BOARD)
                    {
                        node->player.pos += 4 * WH_BOARD;
                    }
                    else
                        printf("deplacement impossible exception sortie board \n");
                }
                else
                    node->player.pos += 2 * WH_BOARD; // on ajoute WH_BOARD a la position dans la grille pour passer sur la ligne au dessous
            }
            else
                printf("Sortie de board");
            break;
        case 3: // gauche
            if (isValidPosition(node, node->player.pos - 2, 0))
            {
                if (node->player.pos - 2 == node->ia.pos)
                {
                    if ((node->player.pos - 4) / WH_BOARD == node->player.pos / WH_BOARD)
                    {
                        node->player.pos -= 4;
                    }
                    else
                        printf("deplacement impossible exception sortie board \n");
                }
                else
                    node->player.pos -= 2; // on retire 2 a la position dans la grille pour passer sur la case a gauche
            }
            else
                printf("Sortie de board");
            break;
        default:
            printf("Indiquez une valeur de déplacement comprise entre 0 et 3 \n");
            break;
        }
        // change la position du joueur sur le board
        node->board[tmp] = 0;
        node->board[node->player.pos] = 1;
    }
    else if (player == 1)
    {                           // ia
        int tmp = node->ia.pos; // garde l'ancienne position de l'ia
        switch (direction)
        {
        case 0:                           // haut
            node->ia.pos -= 2 * WH_BOARD; // on enlève WH_BOARD a la position dans la grille pour monter sur la ligne au dessus
            break;
        case 1:                // droite
            node->ia.pos += 2; // on ajoute 2 a la position dans la grille pour passer sur la case a droite
            break;
        case 2:                           // bas
            node->ia.pos += 2 * WH_BOARD; // on ajoute WH_BOARD a la position dans la grille pour passer sur la ligne au dessous
            break;
        case 3:                // gauche
            node->ia.pos -= 2; // on retire 2 a la position dans la grille pour passer sur la case a gauche
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

// direction == 0 pour horizontal
// direction == 1 pour vertical
// player == 0 pour joueur
// player == 1 pour ia
void putWall(Item *node, int player, int position, int direction)
{
        Item *temp;
        temp=node;
    if (player == 0 && isValidPositionWall(temp, position, direction) == 0)
    {

        printf("position de mur non valide\n");
        return;
    }
    
    // verifications primaires
    assert(temp->board[position] == -1);
    if (player == 0)
        assert(temp->player.wall >= 0);
    if (player == 1)
        assert(temp->ia.wall >= 0);

    switch (direction)
    {
    case 0:                                                                                                        // horizontal
        assert(temp->board[position - 1] == -1 && temp->board[position] == -1 && temp->board[position + 1] == -1); // verifie que c'est un endroit pour murs
        temp->board[position - 1] = -2;
        temp->board[position] = -2;
        temp->board[position + 1] = -2;
        break;
    case 1:                                                                                                                      // vertical
        assert(temp->board[position - WH_BOARD] == -1 && temp->board[position] == -1 && temp->board[position + WH_BOARD] == -1); // verifie que c'est un endroit pour murs
        temp->board[position - WH_BOARD] = -2;
        temp->board[position] = -2;
        temp->board[position + WH_BOARD] = -2;
        break;

    default:
        printf("Indiquez une valeur de direction comprise entre 0 et 1");
        break;
    }
    if (isPathAvailable(temp, temp->player.pos, player, 0, 0) == 0)
    {
        printf("vous pouvez pas mettre de mur ici");
        return;
    }
    else
    {
        printf("mur placé");
        node=temp;
    }

    // on décrémente le nombre de mur restant à placer chez le joueur
    // pour l'ia on le fait dans getchildboard
    if (player == 0)
        node->player.wall--;
}
