/*
** EPITECH PROJECT, 2023
** my_strdup
** File description:
** function that allocates memory
** and copies the string given as a argeument in it
*/

#include <stdlib.h>
#include "../../include/my.h"

char *my_strdup(char const *src)
{
    char *dest;

    dest = malloc(1 * (my_strlen(src) + 1));
    for (int i = 0; i <= my_strlen(src); i++){
        dest[i] = src[i];
    }
    dest[my_strlen(src)] = '\0';
    return (dest);
}
