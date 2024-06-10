/*
** EPITECH PROJECT, 2023
** sig_handler.c
** File description:
** handle signals
*/

/*!
 * @file sig_handler.c
 */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/my.h"
#include <stdlib.h>

/*!
 * function that display a char
 * @param c is the char wanted to be display
 * @return 1
 */
int my_putchar(char c)
{
    return write(1, &c, 1);
}

/*!
 * function which handles the signals in the attack stage
 * @param sig correspond to the type of signals
 */
void sig_handler_attack(int sig)
{
    if (sig == SIGUSR2)
        game_data.sigusr2_count++;
    if (sig == SIGUSR1) {
        game_data.hit++;
    }
}

/*!
 * function which handles the signals in the defense stage
 * @param sig correspond to the type of signal
 */
void sig_handler_wait(int sig)
{
    if (sig == SIGUSR2) {
        game_data.sigusr2_count++;
    }
    if (game_data.sigusr2_count == 1 && sig == SIGUSR1) {
        game_data.x++;
    } else if (game_data.sigusr2_count == 2 && sig == SIGUSR1) {
        game_data.y++;
    }
    if (game_data.sigusr2_count == 3) {
        my_putstr("\nresult: ");
        my_putchar('A' + game_data.x - 1);
        my_putchar('0' + game_data.y);
    }
}

/*!
 * function that handle the signals during the game and redirect it depending
 * on the current phase of the current process.
 * Its params correspond to the one that sigaction use
 * @param signo
 * @param ptr
 * @param pvoid
 */
void sig_handler_game(int signo, siginfo_t *ptr, void *pvoid)
{
    if (game_data.pid2 != ptr->si_pid)
        return;
    if (game_data.attack == 1) {
        sig_handler_attack(signo);
    } else if (game_data.attack == 0) {
        sig_handler_wait(signo);
    }
}
