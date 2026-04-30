/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 14:58:58 by username          #+#    #+#             */
/*   Updated: 2026/04/28 12:32:11 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_coder		t_coder;
typedef struct s_dongle		t_dongle;
typedef struct s_config		t_config;
typedef struct s_request	t_request;

typedef struct s_config
{
	int						number_of_coders;
	int						time_to_burnout;
	int						time_to_compile;
	int						time_to_debug;
	int						time_to_refactor;
	int						number_of_compiles_required;
	int						dongle_cooldown;
	char					*scheduler;

	int						stop_simulation;
	long long				start_time;
	int						ready;

	pthread_mutex_t			stop_simulation_mutex;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			heap_push_mutex;
	pthread_mutex_t			ready_mutex;

	pthread_t				monitor_id;

	t_coder					*coders;
	t_dongle				*dongles;

}							t_config;

typedef struct s_dongle
{
	pthread_mutex_t			availability_mutex;
	pthread_mutex_t			heap_mutex;

	int						is_available;
	long long				last_released;

	t_coder					**heap;
	t_config				*config;

}							t_dongle;

typedef struct s_coder
{
	pthread_t				coder_thread_id;
	pthread_mutex_t			compile_mutex;

	int						id;
	long long				last_compile_time;
	int						compile_count;

	t_dongle				*left_dongle;
	t_dongle				*right_dongle;
	t_config				*config;

}							t_coder;

//main.c
int							main(int argc, char **argv);

//parse_args.c
int							is_number(const char *str);
int							validate_numbers(char **argv);
int							validate_scheduler(const char *scheduler);
int							parse_args(int argc, char **argv);

//init.c
t_config					*init_config(char **argv);
t_dongle					*init_dongles(t_config *config);
t_coder						*init_coders(t_config *config);

//threads_manager.c
void						start_threads(t_config *config);

//simulation_state.c
int							simulation_stopped(t_config *config);
void						stop_simulation(t_config *config);

//coder_states.c
void						compile(t_coder *coder);
void						debug(t_coder *coder);
void						refactor(t_coder *coder);
long long					get_safe_last_compile_time(t_coder *coder);

//dongle_manager.c
int							try_take_dongles(t_coder *coder);
void						release_dongles(t_coder *coder);

//heap_manager.c
void						add_coder_to_heap(t_coder *coder);
void						enqueue_first_time(t_coder *coder);
void						dequeue_from_heap(t_coder *coder);
void						swap_coders(t_coder **heap);
void						sort_dongle_heap(t_dongle *dongle);

//scheduler.c
int							schedule_fifo(t_coder *coder);
int							schedule_edf(t_coder *coder);
int							has_scheduler_turn(t_coder *coder);

//routine.c
int							take_dongles(t_coder *coder);
void						handle_single_coder(t_coder *coder);
void						*coder_routine(void *arg);

//monitor.c

int							check_coders(t_config *config);
void						*monitor_routine(void *arg);

//coder_stats.c
int							get_compile_count(t_coder *coder);
void						increment_compile_count(t_coder *coder);
long long					get_compile_time(t_coder *coder);
void						update_compile_time(t_coder *coder);

//time_io.c
long long					get_time_ms(void);
void						smart_sleep(long time, t_coder *coder);
void						print_status(t_coder *coder, char *msg, int count);

void						lock_dongles_safe(t_coder *coder);
void						unlock_dongles_safe(t_coder *coder);

void						wait_all_threads_ready(t_config *config);

#endif
