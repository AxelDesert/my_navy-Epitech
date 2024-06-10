/*
** EPITECH PROJECT, 2023
** rr
** File description:
** rr
*/

#ifndef MY_H
    #define MY_H
    #include <unistd.h>
    #include <fcntl.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <signal.h>

typedef struct navy_pos_s {
    int length;
    char *pos_x;
    char *pos_y;
    struct navy_pos_s *next;
} navy_pos_t;

typedef struct head_s {
    struct navy_pos_s *head;
} head_t;

typedef struct data_s {
    int x;
    int y;
    int sigusr2_count;
    pid_t pid2;
    int attack;
    int hit;
    int round;
    char **clear_map;
    char **player_map;
    head_t *head;
    int length;
}data_t;

extern data_t game_data;
int my_putchar(char c);
int my_strcmp(char const *s1, char const *s2);
char **my_str_to_word_array(char const *str);
int my_strlen(char const *str);
int parse_file(char *file_path, head_t *headNav);
int my_getnbr_char(char c);
int my_put_nbr(int nb);
int my_putstr(char const *str);
int my_getnbr(char const *str);
void sig_handler_game(int signo, siginfo_t *ptr, void *pvoid);
int attack(void);
int wait(void);
int play(head_t *head);
char *my_strdup(char const *src);
int my_getdigit(char c);
int game(int ac, char **av, pid_t pid, head_t *head);
void print_map(void);
int create_map(head_t *head);
void mark_shot(int def, int i, int j, int hit);
int check_attack(int x, int y);
int is_finished(void);

#endif
