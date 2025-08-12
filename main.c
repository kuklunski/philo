/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:39:02 by ylemkere          #+#    #+#             */
/*   Updated: 2025/08/08 20:39:02 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;
	int		parse_result;

	if (ac == 5 || ac == 6)
	{
		parse_result = check_and_parse(&table, av);
		if (parse_result == -1)
			return (printf("Usage ex: ./philo 5 800 200 200 [3]\n"));
		if (parse_result == -2)
			return (printf("System can't handle timestamps < 60ms\n"));
		if (!data_init(&table))
			return (printf("Failed to initialize data\n"));
		start_dinner(&table);
		clean(&table);
	}
	else
		printf("Usage ex: ./philo 5 800 200 200 [3]\n");
	return (0);
}
