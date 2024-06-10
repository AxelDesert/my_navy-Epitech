/*
** EPITECH PROJECT, 2023
** play_game.c
** File description:
** play game
*/

/*!
 * @file play_game.c
 */
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/my.h"
#include <stdlib.h>

/*!
 * function that initialize values for defense phase and launch the function
 * wait
 * @return 1 if lose or 0 if program need to continue
 */
int defense(void)
{
    my_putstr("\nwaiting for enemy's attack...\n");
    game_data.sigusr2_count = 0;
    game_data.x = 0;
    game_data.y = 0;
    if (wait() == 1)
        return 1;
    game_data.attack = 1;
    game_data.round += 1;
    return 0;
}

/*!
 * function that execute either the attack commend, either the defense
 * command, and display maps every two rounds
 * @param head
 * @return 1 if lose or 2 if win or 0 if the program need to continue
 */
int play_while(head_t *head)
{
    int end = 0;

    if ((game_data.round % 2) == 0)
        print_map();
    if (game_data.attack == 1) {
        game_data.hit = 0;
        game_data.sigusr2_count = 0;
        if (attack() == 2)
            return 2;
        game_data.attack = 0;
        game_data.round += 1;
    } else if (game_data.attack == 0) {
        end = defense();
    }
    if (end == 1)
        return 1;
    return 0;
}

/*!
 * function which initialize the sig_hanlder and really launch th game
 * It will alternate phase of attack or defense, player 1 will start attacking
 * @param head
 * @return 1 if you lose or 0 if you win
 */
int play(head_t *head)
{
    struct sigaction sa;
    int end;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sig_handler_game;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    while (1) {
        end = play_while(head);
        if (end == 1) {
            return 1;
        }
        if (end == 2) {
            return 0;
        }
    }
}
