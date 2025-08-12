/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:39:02 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/08 20:39:02 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (0);
	elapsed = get_current_time() - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	time_to_die = philo->table->time_to_die / 1000;
	if (elapsed > time_to_die)
		return (1);
	else
		return (0);
}

void	*monitor_simulation(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!all_threads_running(&table->table_mutex,
			&table->threads_running_nbr, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				safe_write(table, "died", table->philos[i].id);
			}
		}
		if (table->nbr_limit_meals > 0 && all_philosophers_full(table))
			set_bool(&table->table_mutex, &table->end_simulation, true);
		usleep(5000);
	}
	return (NULL);
}

int	all_philosophers_full(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (!get_bool(&table->philos[i].philo_mutex, &table->philos[i].full))
			return (0);
		i++;
	}
	return (1);
}
