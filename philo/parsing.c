/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:39:02 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/08 20:39:02 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static const char	*input_is_valid(const char *str)
{
	const char	*number;

	while ((*str >= 9 && *str <= 13) || *str == 32)
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		return (NULL);
	if (*str > '9' || *str < '0')
		return (NULL);
	number = str;
	return (number);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = input_is_valid(str);
	if (str == NULL)
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - 48);
		if (num > INT_MAX || num < 0)
			return (-1);
		str++;
	}
	return (num);
}

int	check_and_parse(t_table *table, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atol(av[i]) == -1)
			return (-1);
		i++;
	}
	table->philo_nbr = ft_atol(av[1]);
	if (table->philo_nbr == 0)
		return (-1);
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (table->time_to_die < 60000 || table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
		return (-2);
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5]);
	else
		table->nbr_limit_meals = -1;
	return (0);
}
