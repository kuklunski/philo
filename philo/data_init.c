/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:39:02 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/08 20:39:02 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].full = false;
		table->philos[i].meals_counter = 0;
		table->philos[i].table = table;
		if (pthread_mutex_init(&table->philos[i].philo_mutex, NULL) != 0)
			return (1);
		assign_forks(&table->philos[i], table->forks, i);
		i++;
	}
	return (0);
}

t_table	*data_init_two(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
		{
			destroy_all(table);
			return (NULL);
		}
		table->forks[i].fork_id = i;
		i++;
	}
	if (philo_init(table) != 0)
	{
		destroy_all(table);
		return (NULL);
	}
	return (table);
}

static void	cleanup_init_failure(t_table *table)
{
	free_ptr((void **)&table->philos);
	free_ptr((void **)&table->forks);
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->table_mutex);
}

t_table	*data_init(t_table *table)
{
	t_table	*value;

	if (!table)
		return (NULL);
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->threads_running_nbr = 0;
	if (pthread_mutex_init(&table->table_mutex, NULL) != 0
		|| pthread_mutex_init(&table->write_lock, NULL) != 0)
		return (NULL);
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	if (!table->philos || !table->forks)
	{
		cleanup_init_failure(table);
		return (NULL);
	}
	value = data_init_two(table);
	if (!value)
		return (NULL);
	return (value);
}
