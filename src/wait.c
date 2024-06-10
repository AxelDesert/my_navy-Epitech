/*
** EPITECH PROJECT, 2023
** wait.c
** File description:
** wait for ennemy to attack
*/

/*!
 * @file wait.c
 */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/my.h"
#include <stdlib.h>

/*!
 * function which do the commands i the game is lost
 * @return
 */
int if_finished(void)
{
    kill(game_data.pid2, SIGUSR1);
    usleep(1000);
    kill(game_data.pid2, SIGUSR2);
    usleep(1000);
    print_map();
    my_putstr("\nEnemy won\n");
}

/*!
 * function which check if the attack is missed or hit and send signals
 * corresponding of the situation and update the map
 * @return 1 if lose and 0 if need to continue
 */
int display(void)
{
    if (check_attack(game_data.y + 1, game_data.x) == 1) {
        kill(game_data.pid2, SIGUSR1);
        usleep(1000);
        my_putstr(":hit\n");
        mark_shot(1, game_data.y + 1, game_data.x, 1);
    } else {
        my_putstr(":missed\n");
        mark_shot(1, game_data.y + 1, game_data.x, 0);
    }
    if (is_finished() == 1) {
        if_finished();
        return 1;
    }
    kill(game_data.pid2, SIGUSR2);
    usleep(1000);
    return 0;
}

/*!
 * function which wait for the signals of the first player corresponding to
 * the coordinates and execute display fucntion
 * @return 0 if need to continue or 1 if it's a win
 */
int wait(void)
{
    while (1) {
        pause();
        if (game_data.sigusr2_count == 3) {
            break;
        }
    }
    if (display() == 1)
        return 1;
    return 0;
}
