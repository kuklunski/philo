/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:39:02 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/08 20:39:02 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.5, philo->table);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	safe_write(philo->table, "has taken a fork", philo->id);
	pthread_mutex_lock(&philo->second_fork->fork);
	safe_write(philo->table, "has taken a fork", philo->id);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_current_time());
	philo->meals_counter++;
	safe_write(philo->table, "is eating", philo->id);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->second_fork->fork);
	pthread_mutex_unlock(&philo->first_fork->fork);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	synchro_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_current_time());
	increment_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	de_synchronize_philos(philo);
	while (!simulation_finished(philo->table))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
		eat(philo);
		safe_write(philo->table, "is sleeping", philo->id);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo);
	}
	return (NULL);
}

void	start_dinner(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
	{
		pthread_create(&table->philos[0].thread_id, NULL, single_philo,
			&table->philos[0]);
		pthread_join(table->philos[0].thread_id, NULL);
		return ;
	}
	i = -1;
	while (++i < table->philo_nbr)
		pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation,
			&table->philos[i]);
	pthread_create(&table->monitor, NULL, monitor_simulation, table);
	table->start_simulation = get_current_time();
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	pthread_join(table->monitor, NULL);
}
