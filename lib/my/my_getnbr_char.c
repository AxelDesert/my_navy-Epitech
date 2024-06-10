/*
** EPITECH PROJECT, 2023
** rr
** File description:
** rr
*/

int my_getnbr_char(char c)
{
    int nbr = 0;

    if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
        return ('0' + c);
    return 84;
}
