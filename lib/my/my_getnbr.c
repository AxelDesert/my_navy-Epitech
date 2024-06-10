/*
** EPITECH PROJECT, 2023
** rr
** File description:
** rr
*/

int my_getnbr(char const *str)
{
    int nbr = 0;
    int start = 0;
    int isneg = 1;

    while (str[start] < '0' || str[start] > '9'){
        if (str[start] == '-')
            isneg = isneg * (-1);
        start++;
    }
    for (; str[start] <= '9' && str[start] >= '0'; start++) {
        nbr = nbr * 10 + (str[start] - '0');
        }
    return nbr * isneg;
}
