/*
** EPITECH PROJECT, 2023
** attack.c
** File description:
** will send signal as attack
*/

/*!
 * @file attack.c
 */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/my.h"
#include <stdlib.h>

/*!
 * function that sends coords corresponding by sending signals to the second
 * process
 * @param pid2 is the opponent's pid
 * @param input_buffer if the coords of the attack
 * @return 0
 */
int send_coordinates(pid_t pid2, char *input_buffer)
{
    int x = input_buffer[0] - 'A' + 1;
    int y = input_buffer[1] - '0';

    kill(pid2, SIGUSR2);
    usleep(1000);
    for (int i = 0; i < x; i++) {
        kill(pid2, SIGUSR1);
        usleep(1000);
    }
    kill(pid2, SIGUSR2);
    usleep(1000);
    for (int i = 0; i < y; i++) {
        kill(pid2, SIGUSR1);
        usleep(1000);
    }
    kill(pid2, SIGUSR2);
    usleep(1000);
    return 0;
}

/*!
 * function that check if the player won
 * @return 0 if not and 2 if it is a win
 */
int when_finish(void)
{
    if (game_data.hit == 2) {
        print_map();
        my_putstr("\nI won\n");
        return 2;
    }
    return 0;
}

/*!
 * function that display if the attack hit or miss and update the map
 * @param input_buffer is the coordinates attacked
 * @return return 0 if need to continue or 2 if win
 */
int check_hit(char *input_buffer)
{
    int x = input_buffer[0] - 'A' + 1;
    int y = input_buffer[1] - '0';

    my_putstr("\nresult: ");
    write(1, input_buffer, 2);
    while (game_data.sigusr2_count != 1) {
        pause();
    }
    if (game_data.hit >= 1) {
        my_putstr(":hit\n");
        mark_shot(0, y + 1, x, 1);
    } else {
        my_putstr(":missed\n");
        mark_shot(0, y + 1, x, 0);
    }
    return when_finish();
}

/*!
 * function that get the coordinate you want to attack until its good
 * coordinates and will launch the function to transmit the coords to the
 * other player and check if win or need to continue
 * @return 2 if win and 0 in need to continue
 */
int attack(void)
{
    size_t buffer_size = 0;
    char *input_buffer = NULL;

    while (1) {
        my_putstr("\nattack: ");
        getline(&input_buffer, &buffer_size, stdin);
        if (my_strlen(input_buffer) >= 2 && my_strlen(input_buffer) <= 3
            && input_buffer[0] >= 'A' && input_buffer[0] <= 'H' &&
            input_buffer[1] >= '1' && input_buffer[1] <= '8') {
            send_coordinates(game_data.pid2, input_buffer);
            break;
        } else
            my_putstr("\nwrong position\n");
    }
    if (check_hit(input_buffer) == 2)
        return 2;
    return 0;
}
