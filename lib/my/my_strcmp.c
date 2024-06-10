/*
** EPITECH PROJECT, 2023
** rr
** File description:
** rr
*/

#include "../../include/my.h"

int my_strcmp(char const *s1, char const *s2)
{
    int s1_len = my_strlen(s1);
    int comp = 0;

    for (int i = 0; i <= s1_len; i++) {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
    }
    return 0;
}
