#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
// #include <malloc.h>

#include "List.h"
#include "Board.h"

list_t openList_p;
list_t closedList_p;

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

void bfs(void) // file
{
  Item *cur_node, *child_p, *temp;
  int i;

  while (listCount(&openList_p) != 0)
  { /* While items are on the open list */
    // printf("%d \n", listCount(&openList_p));
    /* Get the first item on the open list */
    cur_node = popFirst(&openList_p);
    // printList(openList_p);
    //  printf("%d  %f\n", listCount(&openList_p), evaluateBoard( cur_node ));

    /* Add it to the "visited" list */
    addLast(&closedList_p, cur_node);
    /* Do we have a solution? */
    if (evaluateBoard(cur_node) == 0.0)
    {

      showSolution(cur_node);
      return;
    }
    else
    {
      /* Enumerate adjacent states */
      for (int i = 0; i < MAX_BOARD; i++)
      {

        child_p = getChildBoard(cur_node, i);
        if (child_p != NULL)
        { // it's a valid child!

          /* Ignore this child if already visited */
          if (onList(&closedList_p, child_p->board) == NULL)
          {
            addLast(&openList_p, child_p);
          }
          /* Add child node to openList */
        }
      }
    }
  }

  return;
}

void dfs(void) // pile
{
  Item *cur_node, *child_p, *temp;
  int i;

  while (listCount(&openList_p) != 0)
  { /* While items are on the open list */
    // printf("%d \n", listCount(&openList_p));
    /* Get the first item on the open list */
    cur_node = popFirst(&openList_p);
    // printList(openList_p);
    // printf("%d  %f\n", listCount(&openList_p), evaluateBoard( cur_node ));

    /* Add it to the "visited" list */
    addLast(&closedList_p, cur_node);
    /* Do we have a solution? */
    if (evaluateBoard(cur_node) == 0.0)
    {

      showSolution(cur_node);
      return;
    }
    else
    {
      /* Enumerate adjacent states */
      for (int i = 0; i < MAX_BOARD; i++)
      {

        child_p = getChildBoard(cur_node, i);
        if (child_p != NULL)
        { // it's a valid child!

          /* Ignore this child if already visited */
          if (onList(&closedList_p, child_p->board) == NULL)
          {
            addFirst(&openList_p, child_p);
          }
          /* Add child node to openList */
        }
      }
    }
  }

  return;
}

void ucs(void)
{
  Item *cur_node, *child_p, *temp;
  int i;

  while (listCount(&openList_p) != 0)
  { /* While items are on the open list */
    // printf("%d\n", listCount(&openList_p));
    /* Get the first item on the open list */
    cur_node = popBest(&openList_p);
    // printList(openList_p);
    //  printf("%d  %f\n", listCount(&openList_p), evaluateBoard( cur_node ));

    /* Add it to the "visited" list */
    addLast(&closedList_p, cur_node);
    /* Do we have a solution? */
    if (evaluateBoard(cur_node) == 0.0)
    {

      showSolution(cur_node);
      return;
    }
    else
    {
      /* Enumerate adjacent states */
      for (int i = 0; i < MAX_BOARD; i++)
      {
        // printf("%lf\n", cur_node->f);
        child_p = getChildBoard(cur_node, i);
        if (child_p != NULL)
        { // it's a valid child!

          temp = onList(&openList_p, child_p->board);
          if (temp != NULL && (temp->f > child_p->f))
          {
            delList(&openList_p, temp);
            addLast(&openList_p, child_p);
          }
          else if (onList(&closedList_p, child_p->board) == NULL && onList(&openList_p, child_p->board) == NULL)
          {
            addLast(&openList_p, child_p);
          }
          /* Add child node to openList */
        }
      }
    }
  }

  return;
}

int main()
{
  printf("\n"); // segmentation error without this line ???
  /* init lists */
  initList(&openList_p);
  initList(&closedList_p);

  printf("\nInitial:");
  Item *initial_state = initGame();
  printBoard(initial_state);

  printf("\nSearching ...\n");

  addLast(&openList_p, initial_state);
  // printList(openList_p);
  dfs();

  printf("Finished!\n");

  /* clean lists */
  cleanupList(&openList_p);
  cleanupList(&closedList_p);

  return 0;
}
