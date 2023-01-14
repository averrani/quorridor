#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
//#include <malloc.h>

#include "list.h"
#include "board.h"
#include "player.h" // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ENLEVER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

list_t openList_p;
list_t closedList_p;


void showSolution( Item *goal )
{
  int i = 0, j;

  printf("\nSolution:");

  while (goal) {
    printBoard( goal );
    goal = goal->parent;
    i++;
  }
  
  printf("\nLength of the solution = %d\n", i-1);
  printf("i");
  printf("Size of open list = %d\n", openList_p.numElements);
  printf("Size of closed list = %d\n", closedList_p.numElements);
  return;
}

/*
int minimax(int isMax){
  int value;
  Item *cur_node = popFirst(&openList_p);
  if(cur_node->depth == 0)
    return cur_node->g; //heuristic
  
  if(isMax){
    value = -100000;
    value = max(value, minimax(getChildBoard(cur_node, i)))

  }
}
*/

int main()
{
  printf("\n"); //segmentation error without this line ???
	/* init lists */
  initList(&openList_p);
  initList(&closedList_p);

	
  printf("\nInitial:");
  Item *initial_state = initGame();
  //printBoard( initial_state );

  printf("\nSearching ...\n");
  
  //movePlayer(initial_state, 0, 1);
  putWall(initial_state, 1, 0);
  printBoard( initial_state );

  addLast( &openList_p, initial_state );
  //printList(openList_p);

  //minimax();
  
	printf("Finished!\n");
  
	/* clean lists */
	cleanupList( &openList_p );
  cleanupList( &closedList_p );
	
  return 0;
}
