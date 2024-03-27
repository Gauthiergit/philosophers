/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:30:53 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/27 15:33:49 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	init_mutex(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->display, NULL);
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->time, NULL);
	pthread_mutex_init(&data->eat, NULL);
}

void	init_philo(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		data->philo[i].thread_id = i + 1;
		data->philo[i].right_fork = i;
		data->philo[i].left_fork = (i + 1) % data->philo_nb;
		data->philo[i].data = data;
		data->philo[i].count_eat = data->eat_nb;
		data->philo[i].start_time.tv_sec = 0;
		data->philo[i].start_time.tv_usec = 0;
		data->philo[i].current_time.tv_sec = 0;
		data->philo[i].current_time.tv_usec = 0;
		i++;
	}
}

void	init_data(t_data *data, char **argv)
{
	data->philo_nb = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]) * 1000;
	data->time_to_eat = ft_atoi(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argv[5])
		data->eat_nb = ft_atoi(argv[5]);
	else
		data->eat_nb = 0;
	data->so_dead = 0;
	data->finish = 0;
	check_sup_zero(data);
	data->forks = malloc(data->philo_nb * sizeof(pthread_mutex_t));
	if (!data->forks)
		exit(1);
	data->philo = malloc(data->philo_nb * sizeof(t_philo));
	if (!data->philo)
		exit(1);
	init_mutex(data);
	init_philo(data);
}
