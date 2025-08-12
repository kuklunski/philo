/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:46:29 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/08 20:46:29 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	long			fork_id;
}	t_fork;

typedef struct s_philo
{
	long			id;
	bool			full;
	long			meals_counter;
	long			last_meal_time;
	pthread_mutex_t	philo_mutex;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	t_table			*table;
}	t_philo;

struct s_table
{
	long			philo_nbr;
	long			time_to_eat;
	long			time_to_die;
	long			time_to_sleep;
	long			nbr_limit_meals;
	long			start_simulation;
	bool			end_simulation;
	bool			all_threads_ready;
	long			threads_running_nbr;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	write_lock;
	pthread_t		monitor;
};

int		check_and_parse(t_table *table, char **av);
t_table	*data_init(t_table *table);
t_table	*data_init_two(t_table *table);
void	destroy_all(t_table *table);
void	assign_forks(t_philo *philo, t_fork *forks, int position);

void	*dinner_simulation(void *data);
void	start_dinner(t_table *table);

void	synchro_all_threads(t_table *table);
void	de_synchronize_philos(t_philo *philo);
bool	all_threads_running(pthread_mutex_t *mutex, long *threads,
			long philo_nbr);
void	increment_long(pthread_mutex_t *mutex, long *value);

void	*monitor_simulation(void *arg);
long	simulation_finished(t_table *table);
int		all_philosophers_full(t_table *table);

void	*single_philo(void *data);

void	thinking(t_philo *philo);
void	eat(t_philo *philo);

long	get_current_time(void);
long	get_current_time_us(void);
void	precise_usleep(long usec, t_table *table);
void	safe_write(t_table *table, char *str, int id);

void	clean(t_table *table);

long	get_long(pthread_mutex_t *mutex, long *dest);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
bool	get_bool(pthread_mutex_t *mutex, bool *dest);
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);

void	free_ptr(void **ptr);
