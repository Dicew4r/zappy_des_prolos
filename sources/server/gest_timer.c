/*
** EPITECH PROJECT, 2018
** loop
** File description:
** server
*/

#include "struct.h"
#include "fcts.h"
#include <pthread.h>

void push(int (*pts)(), t_passing arg)
{
    t_timer *element = malloc(sizeof(t_timer));
    element->pts = arg->pts;
    element->time = arg->
    element->prec = e->time;
    *p = element;
}

void live_alone(t_env *e)
{
        for (int i = 0; i < MAX_FD; i++)
            if (e->fd_type[i] == FD_CLIENT) {
                printf("[%d->%d]\n", i, (int)e->inventory[i].food);
                e->inventory[i].food -= 1;
            }
}

void gest_time(float time, t_env *e, int fd, clock_t tempsdebut)
{
    clock_t tempsFin = clock();
    int delta;

    tempsFin = clock();
    e->inventory[fd].food -= time;
    delta = tempsFin - tempsdebut / CLOCKS_PER_SEC;
    printf("%d\n", delta);


}