#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

#include "player.h"
#include "board.h"

Item *nodeAlloc()
{
    Item *node;

    node = (Item *)malloc(sizeof(Item));
    assert(node);

    node->board = NULL;
    node->parent = NULL;
    node->prev = NULL;
    node->next = NULL;
    node->f = node->g = node->h = (double)0.0;

    return node;
}

// player == 0 pour joueur
// player == 1 pour ia
void movePlayer(Item *node, int direction)
{

    int tmp = node->player.pos; // garde l'ancienne position du joueur
    switch (direction)
    {
    case 0: // haut
        if (isValidPosition(node, node->player.pos - 2 * WH_BOARD, 0))
        {
            if (node->player.pos - 2 * WH_BOARD == node->ia.pos)
            {                                                                                    // on ajoute l'exception si la position ou le joueur veut aller est celle de l'ia
                if ((node->player.pos - 4 * WH_BOARD) % WH_BOARD == node->player.pos % WH_BOARD) // exception pour pas sortir du board en cas de jump
                {
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

void moveIA(Item *node, int pos, int p)
{

    int direction;
    if (p == 0)
    {
        int tmp = node->ia.pos; // garde l'ancienne position de l'ia

        if (pos == node->ia.pos + 2)
            direction = 1;
        if (pos == node->ia.pos - 2)
            direction = 3;
        if (pos == node->ia.pos + 2 * WH_BOARD)
            direction = 2;
        if (pos == node->ia.pos - 2 * WH_BOARD)
            direction = 0;

        switch (direction)
        {
        case 0: // haut
            if (node->ia.pos - 2 * WH_BOARD == node->player.pos)
            {                                                                            // on ajoute l'exception si la position ou le joueur veut aller est celle de l'ia
                if ((node->ia.pos - 4 * WH_BOARD) % WH_BOARD == node->ia.pos % WH_BOARD) // exception pour pas sortir du board en cas de jump
                    node->ia.pos -= 4 * WH_BOARD;                                        // jump
            }
            else
                node->ia.pos -= 2 * WH_BOARD; // on enlève WH_BOARD a la position dans la grille pour monter sur la ligne au dessus
            break;
        case 1: // droite
            if (node->ia.pos + 2 == node->player.pos)
            {
                if ((node->ia.pos + 4) / WH_BOARD == node->ia.pos / WH_BOARD)
                    node->ia.pos += 4;
            }
            else
                node->ia.pos += 2; // on ajoute 2 a la position dans la grille pour passer sur la case a droite
            break;
        case 2: // bas
            if (node->ia.pos + 2 * WH_BOARD == node->player.pos)
            {
                if ((node->ia.pos + 4 * WH_BOARD) % WH_BOARD == node->ia.pos % WH_BOARD)
                    node->ia.pos += 4 * WH_BOARD;
            }
            else
                node->ia.pos += 2 * WH_BOARD; // on ajoute WH_BOARD a la position dans la grille pour passer sur la ligne au dessous
            break;
        case 3: // gauche
            if (node->ia.pos - 2 == node->player.pos)
            {
                if ((node->ia.pos - 4) / WH_BOARD == node->ia.pos / WH_BOARD)
                    node->ia.pos -= 4;
            }
            else
                node->ia.pos -= 2; // on retire 2 a la position dans la grille pour passer sur la case a gauche
            break;
        default:
            break;
        }
        // change la position de l'ia sur le board
        node->board[tmp] = 0;
        node->board[node->ia.pos] = 2;
    }
    else if (p == 1)
    {

        int tmp = node->player.pos; // garde l'ancienne position de l'ia

        if (pos == node->player.pos + 2)
            direction = 1;
        if (pos == node->player.pos - 2)
            direction = 3;
        if (pos == node->player.pos + 2 * WH_BOARD)
            direction = 2;
        if (pos == node->player.pos - 2 * WH_BOARD)
            direction = 0;

        switch (direction)
        {
        case 0: // haut
            if (node->player.pos - 2 * WH_BOARD == node->ia.pos)
            {                                                                                    // on ajoute l'exception si la position ou le joueur veut aller est celle de l'ia
                if ((node->player.pos - 4 * WH_BOARD) % WH_BOARD == node->player.pos % WH_BOARD) // exception pour pas sortir du board en cas de jump
                    node->player.pos -= 4 * WH_BOARD;                                            // jump
            }
            else
                node->player.pos -= 2 * WH_BOARD; // on enlève WH_BOARD a la position dans la grille pour monter sur la ligne au dessus
            break;
        case 1: // droite
            if (node->player.pos + 2 == node->ia.pos)
            {
                if ((node->player.pos + 4) / WH_BOARD == node->player.pos / WH_BOARD)
                    node->player.pos += 4;
            }
            else
                node->player.pos += 2; // on ajoute 2 a la position dans la grille pour passer sur la case a droite
            break;
        case 2: // bas
            if (node->player.pos + 2 * WH_BOARD == node->ia.pos)
            {
                if ((node->player.pos + 4 * WH_BOARD) % WH_BOARD == node->player.pos % WH_BOARD)
                    node->player.pos += 4 * WH_BOARD;
            }
            else
                node->player.pos += 2 * WH_BOARD; // on ajoute WH_BOARD a la position dans la grille pour passer sur la ligne au dessous
            break;
        case 3: // gauche
            if (node->player.pos - 2 == node->ia.pos)
            {
                if ((node->player.pos - 4) / WH_BOARD == node->player.pos / WH_BOARD)
                    node->player.pos -= 4;
            }
            else
                node->player.pos -= 2; // on retire 2 a la position dans la grille pour passer sur la case a gauche
            break;
        default:
            break;
        }
        // change la position de l'ia sur le board
        node->board[tmp] = 0;
        node->board[node->player.pos] = 2;
    }
}

// direction == 0 pour horizontal
// direction == 1 pour vertical
// player == 0 pour joueur
// player == 1 pour ia
void putWall(Item *node, int player, int pos){

Item *temp;
temp=node;
    if(player == 0 && isValidPositionWall(temp, pos) == 0){
        printf("position de mur non valide\n");
        return;
    }

    //verifications primaires
    assert(temp->board[pos] == -1);
    if(player == 0)
        assert(temp->player.wall >= 0); 
    if(player == 1)
        assert(temp->ia.wall >= 0);  

    if(temp->board[pos+1] != -1){ //murs verticaux
        assert(temp->board[pos] == -1 && temp->board[pos+WH_BOARD] == -1 && temp->board[pos+2*WH_BOARD] == -1 ); // verifie que c'est un endroit pour murs
        temp->board[pos] = -2;
        temp->board[pos+WH_BOARD] = -2;
        temp->board[pos+ 2*WH_BOARD] = -2;
    }else{ //murs horizontaux
        assert(temp->board[pos] == -1 && temp->board[pos+1] == -1 && temp->board[pos+2] == -1 ); // verifie que c'est un endroit pour murs
        temp->board[pos] = -2;
        temp->board[pos+1] = -2;
        temp->board[pos+2] = -2;
    }

    if (isPathAvailable(temp, temp->player.pos, player, 0, 0) == 0)
    {
        printf("vous pouvez pas mettre de mur ici");
        return;
    }
    else
    {
        printf("mur placé");
        node = temp;
    }
    //on décrémente le nombre de mur restant à placer chez le joueur
    //pour l'ia on le fait dans getchildboard
    if(player == 0)
        node->player.wall--; 
}
