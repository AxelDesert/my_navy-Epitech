/*
** EPITECH PROJECT, 2023
** rr
** File description:
** rr
*/

#include <unistd.h>
#include "../../include/my.h"

int my_put_nbr(int nb)
{
    char car;

    if (nb >= 10) {
        my_put_nbr(nb / 10);
        car = '0' + (nb % 10);
        write(1, &car, 1);
    } else {
        car = '0' + (nb % 10);
        write(1, &car, 1);
    }
    return 0;
}
