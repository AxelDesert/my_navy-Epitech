/*
** EPITECH PROJECT, 2023
** rr
** File description:
** rr
*/

/*!
 * @file map_boats.c
 */
#include "../include/my.h"

/*!
 * Place a boat if it is horizontal
 * @param i the variable that go through the string of the array
 * @param j the variable that gp through each letter of a string
 * @param current the current node of the linked list
 */
static void place_boat_horizontal(int i, int j, navy_pos_t *current)
{
    for (int k = 0; k < current->length; k++) {
        game_data.player_map[i][j] = ('0' + current->length);
        j += 2;
    }
}

/*!
 * Place a boat if it is horizontal
 * @param i the variable that go through the string of the array
 * @param j the variable that gp through each letter of a string
 * @param current the current node of the linked list
 */
static void place_boat_vertical(int i, int j, navy_pos_t *current)
{
    for (int k = 0; k < current->length; k++) {
        game_data.player_map[i][j] = ('0' + current->length);
        i++;
    }
}

/*!
 * Place boat on our map
 * @param current the current node of the linked list
 */
static void place_entire_boat(navy_pos_t *current)
{
    int i = 0;
    int j = 0;
    int is_horizontal = 0;

    if (current->pos_y[0] - current->pos_x[0] == (current->length - 1))
        is_horizontal = 1;
    for (; game_data.player_map[i][0] != current->pos_x[1]; i++);
    for (; game_data.player_map[0][j] != current->pos_x[0]; j++);
    if (is_horizontal == 1)
        place_boat_horizontal(i, j, current);
    else
        place_boat_vertical(i, j, current);
}

/*!
 * Place the boat
 * @param i go through the string of the map
 * @param current node of the linked list
 */
void check_y(int i, navy_pos_t *current)
{
    for (int j = 2; game_data.player_map[i][j] != '\0'; j += 2) {
        if (game_data.player_map[0][j] == current->pos_x[0]) {
            game_data.player_map[i][j] = ('0' + current->length);
        }
    }
}

/*!
 * Place the boat
 * @param current node of the linked list
 */
void check_x(navy_pos_t *current)
{
    for (int i = 0; game_data.player_map[i] != NULL; i++) {
        if (game_data.player_map[i][0] == current->pos_x[1]) {
            check_y(i, current);
        }
    }
}

/*!
 * The principal function that that calls others to fill the map with boats
 * @param head head of the linked list
 */
static void fill_player_map(head_t *head)
{
    navy_pos_t *current = head->head;

    while (current != NULL) {
        check_x(current);
        current = current->next;
    }
    current = head->head;
    while (current != NULL) {
        place_entire_boat(current);
        current = current->next;
    }
}

/*!
 * Allocate memory for a map
 * @return a clear map
 */
char **clear_map(void)
{
    char **clear_map = malloc(sizeof(char *) * 11);

    clear_map[0] = my_strdup(" |A B C D E F G H");
    clear_map[1] = my_strdup("-+---------------");
    clear_map[2] = my_strdup("1|. . . . . . . .");
    clear_map[3] = my_strdup("2|. . . . . . . .");
    clear_map[4] = my_strdup("3|. . . . . . . .");
    clear_map[5] = my_strdup("4|. . . . . . . .");
    clear_map[6] = my_strdup("5|. . . . . . . .");
    clear_map[7] = my_strdup("6|. . . . . . . .");
    clear_map[8] = my_strdup("7|. . . . . . . .");
    clear_map[9] = my_strdup("8|. . . . . . . .");
    clear_map[10] = NULL;
    return clear_map;
}

/*!
 * Put the two maps in the global variable
 * @param head the head of the linked list
 * @return nothing
 */
int create_map(head_t *head)
{
    char **map = clear_map();
    char **player_map = clear_map();

    game_data.player_map = player_map;
    game_data.clear_map = map;
    fill_player_map(head);
    return 0;
}

/*!
 * Display our map and the map of the enemy (with no boats of course)
 */
void print_map(void)
{
    write(1, "\nmy navy:\n", my_strlen("\nmy navy:\n"));
    for (int i = 0; game_data.player_map[i] != NULL; i++) {
        write(1, game_data.player_map[i]
        , my_strlen(game_data.player_map[i]));
        write(1, "\n", 1);
    }
    write(1, "\nenemy navy:\n", my_strlen("\nenemy navy:\n"));
    for (int i = 0; game_data.clear_map[i] != NULL; i++) {
        write(1, game_data.clear_map[i]
        , my_strlen(game_data.clear_map[i]));
        write(1, "\n", 1);
    }
}
