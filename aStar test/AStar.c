#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
/* and not not_eq */
#include <iso646.h>
/* add -lm to command line to compile with this header */
#include <math.h>

#define map_size_rows 10
#define map_size_cols 10

char map[map_size_rows][map_size_cols] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

// char map[map_size_rows][map_size_cols] = {
//     {-2, -2, -2, -2, -2, -2, -2, -2, -2, -2},
//     {-2,  0, -1,  0, -1,  0, -1,  0, -1, -2},
//     {-2, -1, -1, -1, -1, -1, -1, -1, -1, -2},
//     {-2,  0, -1,  0, -1,  0, -1,  0, -1, -2},
//     {-2, -1, -1, -1, -1, -1, -1, -1, -1, -2},
//     {-2,  0, -1,  0, -1,  0, -1,  0, -1, -2},
//     {-2, -1, -1, -1, -1, -1, -1, -1, -1, -2},
//     {-2,  0, -1,  0, -1,  0, -1,  0, -1, -2},
//     {-2, -1, -1, -1, -1, -1, -1, -1, -1, -2},
//     {-2, -2, -2, -2, -2, -2, -2, -2, -2, -2}};
/* description of graph node */
struct stop
{
    double col, row;
    /* array of indexes of routes from this stop to neighbours in array of all routes */
    int *n;
    int n_len;
    double f, g, h; // cout total, distance de l'arrivé, distance du départ
    int from;
};

int ind[map_size_rows][map_size_cols] = {
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};

/* description of route between two nodes */
struct route//trace le chemin entre les deux buts

{
    /* route has only one direction! */
    int x; /* index of stop in array of all stops of src of this route */
    int y; /* intex of stop in array of all stops od dst of this route */
    double d;
};

void freestop(struct stop s)
{
    s.col = 0;
    s.row = 0;
    s.n = NULL;
    s.n_len = NULL;
    s.f = DBL_MAX;
    s.g = DBL_MAX;
    s.h = DBL_MAX;
    s.from = 0;
}

int main()
{
    int i, j, k, l, b, found;
    int p_len = 0;
    int *path = NULL;
    int c_len = 0;
    int *closed = NULL;
    int o_len = 1;
    int *open = (int *)calloc(o_len, sizeof(int));
    double min, tempg;
    int s;
    int e;
    int current;
    int s_len = 0;
    struct stop *stops = NULL;
    int r_len = 0;
    struct route *routes = NULL;

    // affecte a ind(i)(j) une valeur t != de 0
    for (i = 1; i < map_size_rows - 1; i++)
    {
        for (j = 1; j < map_size_cols - 1; j++)
        {
            if (map[i][j]!=1)
            {
                printf("a"); // 0 on rentre dans le if 1 on rentr pas
                ++s_len;
                // augmente l'indice de la taille du nombre de stop possible
                stops = (struct stop *)realloc(stops, s_len * sizeof(struct stop)); // augmente la taille du tableau de stop
                int t = s_len - 1;
                stops[t].col = j;
                stops[t].row = i;

                stops[t].from = -1;
                stops[t].g = DBL_MAX; // comprend pas
                stops[t].n_len = 0;
                stops[t].n = NULL;
                ind[i][j] = t;
                // if(abs(stops[t].col-stops[t-1].col)+abs(stops[t].row-stops[t-1].row)<2)
                // {
                //     --s_len;

                //     stops = (struct stop *)realloc(stops, s_len * sizeof(struct stop));

                // }
                // affecte a ind(i)(j) la valeur t = s_len-1
            }
        }
    }

    /* index of start stop */
    s = 0;
    /* index of finish stop */
    e = s_len - 1;

    // Distance entre case stop(e)(l'arrivé) et case courante(i) stocker dans stop.h(i)
    for (i = 0; i < s_len; i++)
    {
         stops[i].h = (stops[e].row - stops[i].row) + (stops[e].col - stops[i].col);
         
        // stops[i].h = sqrt(pow(stops[e].row - stops[i].row, 2) + pow(stops[e].col - stops[i].col, 2)); // distance de l'arrivé de tous les points de stops
    }

    for (i = 2; i < map_size_rows - 1; i++)
    {
        for (j = 2; j < map_size_cols - 1; j++)
        {
            if (ind[i][j] >= 0) // verifie si c'est une case deja visité par stop où déplacement possible
            {
                for (k = i - 1; k <= i + 1; k+=2)//gère quel type de déplacement est possible diagonale uniquement par es coté etc.
                {
                    for (l = j - 1; l <= j + 1; l+=2)
                    {
                         if ((k == i) and (l == j))
                         {
                             continue;
                         }
                        // if (abs(i-k)+abs(j-l)==2)
                        // {
                             if (ind[k][l] >= 0) // incompréhensible
                        {
                            printf("b");
                            ++r_len;
                            routes = (struct route *)realloc(routes, r_len * sizeof(struct route));
                            int t = r_len - 1;
                            routes[t].x = ind[i][j];
                            routes[t].y = ind[k][l];
                            routes[t].d = (stops[routes[t].y].row - stops[routes[t].x].row) + (stops[routes[t].y].col - stops[routes[t].x].col);
                           
                            // routes[t].d = sqrt(pow(stops[routes[t].y].row - stops[routes[t].x].row, 2) + pow(stops[routes[t].y].col - stops[routes[t].x].col, 2)); // distance entre
                            ++stops[routes[t].x].n_len;
                            stops[routes[t].x].n = (int *)realloc(stops[routes[t].x].n, stops[routes[t].x].n_len * sizeof(int));
                            stops[routes[t].x].n[stops[routes[t].x].n_len - 1] = t;
                        }
                        // }
                        
                        
                        if ((k == i) and (l == j))
                         {
                             continue;
                         }
                       
                    }
                }
            }
        }
    }

    open[0] = s;
    stops[s].g = 0;                       // distance du départ et .h distance de l'arrivé
    stops[s].f = stops[s].g + stops[s].h; // coût total des chemin
    found = 0;                            // test si on est arruvé a destination

    while (o_len and not found) // tant que o_len =! NULL et found =! 1
    {
        min = DBL_MAX; // permet d'avoir la valeur max des doubles et donc tout nombre comparé a min pour la première fois prendra forcément la place de min.

        for (i = 0; i < o_len; i++)
        {
            if (stops[open[i]].f < min) // regarde si le node qu'on regarde à un coût plus faible que celui actuel
            {

                current = open[i]; // continue le deplacement du snake vers le coût le plus faible.
                min = stops[open[i]].f;
            }
        }

        if (current == e) // regarde si on est arrivé à destination
        {
            found = 1; // definé qu'on a trouvé

            ++p_len;
            path = (int *)realloc(path, p_len * sizeof(int));
            path[p_len - 1] = current;
            while (stops[current].from >= 0)
            {
                current = stops[current].from; // retrace le chemin dans le sens inverse (je crois)
                ++p_len;
                path = (int *)realloc(path, p_len * sizeof(int));
                path[p_len - 1] = current;
            }
        }

        for (i = 0; i < o_len; i++)
        {
            if (open[i] == current)
            {
                if (i not_eq (o_len - 1))
                {
                    for (j = i; j < (o_len - 1); j++)
                    {
                        open[j] = open[j + 1];
                    }
                }
                --o_len;
                open = (int *)realloc(open, o_len * sizeof(int));
                break;
            }
        }

        ++c_len;
        closed = (int *)realloc(closed, c_len * sizeof(int));
        closed[c_len - 1] = current;

        for (i = 0; i < stops[current].n_len; i++)
        {
            b = 0;

            for (j = 0; j < c_len; j++)
            {
                if (routes[stops[current].n[i]].y == closed[j])
                {
                    b = 1;
                }
            }

            if (b)
            {
                continue;
            }

            tempg = stops[current].g + routes[stops[current].n[i]].d;

            b = 1;

            if (o_len > 0)
            {
                for (j = 0; j < o_len; j++)
                {
                    if (routes[stops[current].n[i]].y == open[j])
                    {
                        b = 0;
                    }
                }
            }

            if (b or (tempg < stops[routes[stops[current].n[i]].y].g)) //??????????????????????????????????????
            {
                stops[routes[stops[current].n[i]].y].from = current;
                stops[routes[stops[current].n[i]].y].g = tempg;
                stops[routes[stops[current].n[i]].y].f = stops[routes[stops[current].n[i]].y].g + stops[routes[stops[current].n[i]].y].h;

                if (b)
                {
                    ++o_len;
                    open = (int *)realloc(open, o_len * sizeof(int));
                    open[o_len - 1] = routes[stops[current].n[i]].y;
                }
            }
        }
    }
    // print board ind
    for (i = 0; i < map_size_rows; i++)
    {
        for (j = 0; j < map_size_cols; j++)
        {
            if (ind[i][j])
            {
                putchar(0xdb);
            }
            else
            {

                putchar('.');
            }
        }
        putchar('\n');
    }

    // PRINT BOARD map

    for (i = 0; i < map_size_rows; i++)
    {
        for (j = 0; j < map_size_cols; j++)
        {
            if (map[i][j])
            {
                putchar(0xdb);
            }
            else
            {
                b = 0;
                for (k = 0; k < p_len; k++)
                {
                    if (ind[i][j] == path[k])
                    {
                        ++b;
                    }
                }
                if (b)
                {
                    putchar('x');
                }
                else
                {
                    putchar('.');
                }
            }
        }
        putchar('\n');
    }

    if (not found)
    {
        puts("IMPOSSIBLE");
    }
    else
    {
        printf("path cost is %d:\n", p_len);
        for (i = p_len - 1; i >= 0; i--)
        {
            printf("(%1.0f, %1.0f)\n", stops[path[i]].col, stops[path[i]].row);
            //     if (i>2)
            //     {
            //          printf("(%1.0f)\n",stops[path[i]].f-stops[path[i-2]].f);
            // }
        }
    }

    for (i = 0; i < s_len; ++i)
    {
        free(stops[i].n);
    }
    free(stops);
    free(routes);
    free(path);
    free(open);
    free(closed);

    return 0;
}