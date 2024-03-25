/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:18:40 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/25 13:02:21 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	check_cara(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

void	init_data(t_data *data, char **argv)
{
	data->philo_nb = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]) * 1000;
	data->time_to_eat = ft_atoi(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi(argv[4]) * 1000;
	data->so_dead = 0;
	if (!data->philo_nb || !data->time_to_die || !data->time_to_sleep
		|| !data->time_to_eat)
	{
		printf("Numbers must be greater than zero\n");
		exit(1);
	}
	data->forks = malloc(data->philo_nb * sizeof(pthread_mutex_t));
	if (!data->forks)
		exit(1);
	data->philo = malloc(data->philo_nb * sizeof(t_philo));
	if (!data->philo)
		exit(1);
	init_mutex(data);
	init_philo(data);
}

void	check_error(int argc, char **argv, t_data *data)
{
	int	i;

	/* if (argc < 5)
	{
		printf("You have to use at least 5 arguments\n");
		exit(1);
	} */
	i = 1;
	while (i < argc)
	{
		if (check_cara(argv[i]))
		{
			printf("Program accept only numeric arguments\n");
			exit(1);
		}
		i++;
	}
	init_data(data, argv);
}
