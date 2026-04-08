/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 14:58:58 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/08 14:43:24 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
#define CODEXION_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <pthread.h>

//#include <xxxxxx.h>

typedef struct s_coder t_coder;
typedef struct s_dongle t_dongle;
typedef struct s_config t_config;


typedef struct s_config
{
    int number_of_coders;

    int time_to_burnout;
    int time_to_compile;
    int time_to_debug;
    int time_to_refactor;

    int number_of_compiles_required;
    int dongle_cooldown;
    char *scheduler;
    long long start_time;

    int burned_out;

    pthread_mutex_t burned_out_mutex;
    pthread_mutex_t print_mutex;

    pthread_cond_t dongles_cond;

    pthread_t monitor;

    t_coder *coders;
    t_dongle *dongles;

} t_config;

typedef struct s_dongle
{
    pthread_mutex_t mutex;
    int is_available;
    long long last_released;

} t_dongle;

typedef struct s_coder
{
    int id;

    long long last_compile_time;
    int compile_count;

    t_dongle *left_dongle;
    t_dongle *right_dongle;

    pthread_t coder_thread;

    t_config *config;

} t_coder;

//parsing
int parse_args(int argc, char **argv);

//initializion
t_config *fill_config(char **argv);
t_dongle    *init_dongles(t_config *config);
t_coder    *init_coders(t_config *config);

//base function
void    start_threads(t_config *config);
int start_monitor(t_config *config);
void    *coder_routine(void *arg);

//utils
long long get_time_ms(void);
void print_status(t_coder *coder, char *msg);
void smart_sleep(t_config *config);

//coder actions
void compile(t_coder *coder);
void debug(t_coder *coder);
void refactor(t_coder *coder);


#endif