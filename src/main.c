/*
** EPITECH PROJECT, 2023
** rr
** File description:
** rr
*/

/*!
 * @file main.c
 */

#include "../include/my.h"

data_t game_data =
{.x = 0, .y = 0, .sigusr2_count = 0, .attack = 0, .hit = 0, .round = 0};

/*!
 * fuction which display the usage of the project
 * @return 0 if error or not
 */
int print_usage(void)
{
    char *line_buf = NULL;
    int line_count = 0;
    FILE *fp = fopen("usage.txt", "r");
    size_t line_buf_size = 0;
    ssize_t line_size;

    if (fp == NULL)
        return 0;
    line_size = getline(&line_buf, &line_buf_size, fp);
    while (line_size >= 0) {
        line_count++;
        write(1, line_buf, my_strlen(line_buf));
        line_size = getline(&line_buf, &line_buf_size, fp);
    }
    fclose(fp);
    return 0;
}

int error_handling_file(int argc, char **argv)
{
    return 0;
}

/*!
 * main function of the project, it will parse_file which check if the second
 * argv is good, it also do some error handling, get the pid of the process
 * and finally will lunch the connection rpocess between terminals
 * @param argc correspond to the lenght of argv, either two or three
 * @param argv first argv correspond to the binary, then if its the first
 * process the second one is the map. If this is the second project the
 * second is the pid of the first process and the map
 * @return the function game which return 84 if error, 0 if you win and 1 in
 * case of lose
 */
int main(int argc, char **argv)
{
    int err = 0;
    head_t *head = malloc(sizeof(head_t));
    pid_t pid = getpid();

    head->head = NULL;
    game_data.head = head;
    if (argc == 2 && my_strcmp(argv[1], "-h") == 0)
        return print_usage();
    if (argc < 2 || argc > 3)
        return 84;
    if (argc == 2)
        err = parse_file(argv[1], head);
    if (argc == 3)
        err = parse_file(argv[2], head);
    if (err == 84)
        return 84;
    return game(argc, argv, pid, head);
}
