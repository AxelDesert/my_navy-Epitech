/*
** EPITECH PROJECT, 2023
** rr
** File description:
** rr
*/

/*!
 * @file parsing.c
 */

#include "../include/my.h"

/*!
 * Add infos of the line in a new node
 * @param boat_infos Informations of the line
 * @param head head of the linked list
 * @return return nothing
 */

int new_boat_node(char **boat_infos, head_t *head)
{
    navy_pos_t *new_node = malloc(sizeof(navy_pos_t));

    new_node->pos_x = malloc(my_strlen(boat_infos[1]));
    new_node->pos_y = malloc(my_strlen(boat_infos[2]));
    new_node->length = my_getnbr(boat_infos[0]);
    new_node->pos_x = boat_infos[1];
    new_node->pos_y = boat_infos[2];
    if (head->head == NULL) {
        new_node->next = NULL;
        head->head = new_node;
        return 0;
    }
    new_node->next = head->head;
    head->head = new_node;
    return 0;
}

/*!
 * Check the informations of the boat
 * @param line Informations of a single line
 * @return 84 if there is an error, 0 if not
 */
int check_infos(char **line)
{
    int length = 2;
    int i = 0;

    for (; line[i] != 0; i++);
    if (i != 3)
        return 84;
    if (my_getnbr(line[0]) < 2 || my_getnbr(line[0]) > 5)
        return 84;
    if (my_strlen(line[1]) != 2 || my_strlen(line[2]) != 2)
        return 84;
    if (line[1][0] != line[2][0] && line[1][1] != line[2][1])
        return 84;
    length = my_getnbr(line[0]);
    if ((my_getnbr_char(line[2][1]) - my_getnbr_char(line[1][1])) !=
        (length - 1) && line[2][0] == line[1][0])
        return 84;
    if (line[2][0] - line[1][0] != (length - 1) && line[2][1] == line[1][1])
        return 84;
    return 0;
}

/*!
 * Compare coordinates
 * @param c_one coordinates one
 * @param c_two coordinates two
 * @return 0 if the coordinates are the same,
 * -1 if c_one is inferior than c_two
 */
static int coor_cmp(char *c_one, char *c_two)
{
    if (c_one[1] < c_two[1]) {
        return -1;
    } else if (c_one[1] > c_two[1]) {
        return 1;
    } else {
        return 0;
    }
}

/*!
 * Compare coordinates
 * @param c_one coordinates one
 * @param c_two coordinates two
 * @return the result of coor_cmp, -1 if c_one is inferior than c_two
 */
static int coordonates_cmp(char *c_one, char *c_two)
{
    if (c_one[0] < c_two[0]) {
        return -1;
    } else if (c_one[0] > c_two[0]) {
        return 1;
    } else {
        return coor_cmp(c_one, c_two);
    }
}

/*!
 * Check if two boats are overwriting by calling the function coordonates_cmp
 * @param boat_one First node to compare
 * @param boat_two Second node to compare
 * @return if two boats are overwriting return 1 else return 0
 */
int is_overwriting(navy_pos_t *boat_one, navy_pos_t *boat_two)
{
    if (coordonates_cmp(boat_one->pos_x, boat_two->pos_y) <= 0 &&
        coordonates_cmp(boat_one->pos_y, boat_two->pos_x) >= 0)
        return 1;
    return 0;
}

/*!
 * Check in the whole linked list if two boats are overwriting
 * @param head The head that points to the first node of a linked list
 * @return 1 if two boats are overwriting, 0 if not
 */
int check_overwrite(head_t *head)
{
    navy_pos_t *i = head->head;
    navy_pos_t *j;
    int err = 0;

    for (; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            err = is_overwriting(i, j);
        }
    }
    if (err == 1)
        return 1;
    return 0;
}

/*!
 * Check informations of boats by calling the function check_infos
 * @param line_buf The buffer of a line of the file
 * @return boat_infos if there isn't error, NULL if there is error
 */
static char **parsing_boat(char *line_buf)
{
    char **boat_infos;

    if (my_getdigit(line_buf[0]) != game_data.length)
        return NULL;
    boat_infos = my_str_to_word_array(line_buf);
    if (check_infos(boat_infos) == 84)
        return NULL;
    new_boat_node(boat_infos, game_data.head);
    return boat_infos;
}

/*!
 * Check if the file is a text and check if line isn't
 * @param line_buf Buffer of the line
 * @param fp File descriptor of the file
 * @return 84 if there is an error, 0 if not
 */
static int error(FILE *fp)
{
    if (fp == NULL) {
        write(2, "Incorrect or non-existent filepath", 35);
        return 84;
    }
    return 0;
}

/*!
 * Parse every lines of the file in parameters by calling parsing_boat, getline
 * check_overwrite
 * @param file_path The path to the file to get informations of
 * @param headNav The head of the linked list with every boat
 * @return 84 if there is an error, 0 if not
 */
int parse_file(char *file_path, head_t *headNav)
{
    char *line_buf = NULL;
    FILE *fp = fopen(file_path, "r");
    size_t line_buf_size = 0;
    ssize_t line_size;

    game_data.length = 2;
    if (error(fp) == 84)
        return 84;
    line_size = getline(&line_buf, &line_buf_size, fp);
    if (my_strlen(line_buf) == 0)
        return 84;
    while (line_size >= 0) {
        if (parsing_boat(line_buf) == NULL)
            return 84;
        game_data.length++;
        line_size = getline(&line_buf, &line_buf_size, fp);
    }
    if (check_overwrite(headNav) == 1)
        return 84;
    return 0;
}
