/*
** EPITECH PROJECT, 2023
** rr
** File description:
** rr
*/

#include "../../include/my.h"
#include <stdlib.h>

int is_alpha_numeric(char c)
{
    if ((c <= 57 && c >= 48) ||
        (c <= 90 && c >= 65) ||
        (c <= 122 && c >= 97))
        return 1;
    return 0;
}

int nbr_of_words(char const *str)
{
    int words = 0;

    for (int i = 0; i < my_strlen(str); i++) {
        if (is_alpha_numeric(str[i]) == 1 && is_alpha_numeric(str[i + 1]) == 0)
            words++;
    }
    return words;
}

char **memo_alloc(char const *str)
{
    int alloc_size = 0;
    int count = 0;
    int tab_size = nbr_of_words(str);
    char **word_array = 0;

    if (tab_size == 0)
        return 0;
    word_array = malloc(sizeof(char *) * (tab_size + 1));
    for (int j = 0; j < my_strlen(str); j++) {
        if (is_alpha_numeric(str[j]) == 1)
            alloc_size++;
        if (is_alpha_numeric(str[j]) == 1 && is_alpha_numeric(str[j + 1])
            == 0){
            word_array[count] = malloc(sizeof(char) * (alloc_size + 1));
            alloc_size = 0;
            count++;
        }
    }
    word_array[tab_size] = 0;
    return word_array;
}

char **put_in_tab(char **word_array, char const *str)
{
    int count = 0;
    int index = 0;

    for (int i = 0; i < my_strlen(str); i++) {
        if (is_alpha_numeric(str[i]) == 1) {
            word_array[count][index] = str[i];
            index++;
        }
        if (is_alpha_numeric(str[i]) == 1 && is_alpha_numeric(str[i + 1])
        == 0) {
            word_array[count][index] = '\0';
            count++;
            index = 0;
        }
    }
    return word_array;
}

char **my_str_to_word_array(char const *str)
{
    char **word_array = memo_alloc(str);

    put_in_tab(word_array, str);
    return word_array;
}
