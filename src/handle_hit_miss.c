/*
** EPITECH PROJECT, 2023
** rr
** File description:
** rr
*/

/*!
 * @file handle_hit_miss.c
 */
#include "../include/my.h"

/*!
 *  Check if the character in param is between 2 and 5
 * @param c is the character to check
 * @return 1 if it's between 2 and 5, and 0 if not
 */
static int is_nbr(char c)
{
    if (c >= '2' && c <= '5')
        return 1;
    return 0;
}

/*!
 * Check if the attack of the player hit or not
 * @param x is the coordinates x of the shot
 * @param y is the coordinates y of the shot
 * @return 1 if the shot hit, 0 if not
 */
int check_attack(int x, int y)
{
    int i = 2;
    int j = 2;

    for (; i < x; i++);
    for (; game_data.player_map[0][j] != (y + 'A' - 1); j += 2);
    if (is_nbr(game_data.player_map[i][j]) == 1)
        return 1;
    return 0;
}

/*!
 * The function mark the shot on the player map and the enemy map
 * @param def if def = 1 it means that we got to write on our map, if it's 0
 * we mark the shot on the enemy map
 * @param i is the coordinates x of the shot
 * @param j is the coordinates y of the shot
 * @param hit if the shot hit we mark a 'x', otherwise we mark with a 'o'
 */
void mark_shot(int def, int i, int j, int hit)
{
    j = j * 2;
    if (def == 0) {
        if (hit == 1)
            game_data.clear_map[i][j] = 'x';
        if (hit == 0 && game_data.clear_map[i][j] != 'x')
            game_data.clear_map[i][j] = 'o';
        return;
    }
    if (def == 1) {
        if (hit == 1)
            game_data.player_map[i][j] = 'x';
        if (hit == 0 && game_data.clear_map[i][j] != 'x')
            game_data.player_map[i][j] = 'o';
    }
}

/*!
 * Check if the game is finished or not by checking if there is any number on
 * the map yet
 * @return return 0 if the game is finished, 1 if not
 */
int is_finished(void)
{
    int count = 0;

    for (int i = 2; game_data.player_map[i] != NULL; i++) {
        for (int j = 2; game_data.player_map[i][j] != '\0'; j++) {
            count += is_nbr(game_data.player_map[i][j]);
        }
    }
    if (count > 0)
        return 0;
    return 1;
}
