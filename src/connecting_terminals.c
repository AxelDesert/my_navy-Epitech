/*
** EPITECH PROJECT, 2023
** connecting_terminals.c
** File description:
** connect two players
*/

/*!
 * @file connecting_terminals.c
 */
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/my.h"
#include <stdlib.h>

/*!
 * sig hangler of the function connect_player to get ennemi pid
 * @param sig = type of signals
 * @param info
 * @param context
 */
void sig_handler(int sig, siginfo_t *info, void *context)
{
    if (sig == SIGUSR1) {
        game_data.pid2 = info->si_pid;
    }
}

/*!
 * function to connect the first player to the second one
 * @param pid is the pid of the current process
 * @return either 84 if error or 0 if success
 */
int connect_first_player(pid_t pid)
{
    my_putstr("my_pid: ");
    my_put_nbr((int)pid);
    my_putstr("\n\nwaiting for enemy...\n\n");
    pause();
    if (kill(game_data.pid2, SIGUSR1) == -1)
        return 84;
    pause();
    my_putstr("enemy connected\n");
    return 0;
}

/*!
 * will send signals to connect to the first process
 * @param pid is the pid of the current process
 * @param pid_opponent is the pid of the opponent process
 * @return return 84 if cant connect and 0 if it works
 */
int conect_second_player(pid_t pid, char *pid_opponent)
{
    game_data.pid2 = my_getnbr(pid_opponent);
    my_putstr("my_pid: ");
    my_put_nbr((int)pid);
    if (kill(game_data.pid2, SIGUSR1) == -1)
        return 84;
    pause();
    kill(game_data.pid2, SIGUSR1);
    my_putstr("\n\nsuccessfully connected to enemy\n");
    return 0;
}

/*!
 * will check which type of connection is needed : if its the first player to
 * launch of the second one
 * @param ac is the argc of main
 * @param av is the argv of main
 * @param pid is the pid of the current process
 * @return either 1 if lose 0 if win and 84 if error
 */
int connect_players(int ac, char **av, pid_t pid)
{
    struct sigaction act;

    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = sig_handler;
    sigaction(SIGUSR1, &act, NULL);
    if (ac == 2) {
        return connect_first_player(pid);
    } else if (ac == 3) {
        return conect_second_player(pid, av[1]);
    }
    return 84;
}

/*!
 * function that will call connect_players function to connect player and if
 * it succeed will
 * @param ac correspond to the argc of the main
 * @param av  correspond to the argv of the main
 * @param pid is the pid of the current process
 * @param head is a structure
 * @return function play that return 1 in case of lose and 0 in case of win
 * or 84 in case of error
 */
int game(int ac, char **av, pid_t pid, head_t *head)
{
    if (connect_players(ac, av, pid) == 84)
        return 84;
    create_map(head);
    if (ac == 2) {
        game_data.attack = 1;
        return play(head);
    } else {
        return play(head);
    }
}
