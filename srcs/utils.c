/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:41:11 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/22 17:36:31 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philosopher.h"

long long int	ft_atoi(const char *str)
{
	long long int	i;
	long long int	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result);
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->mutex, NULL);
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		data->philo[i].thread_id = i;
		data->philo[i].right_fork = i;
		data->philo[i].left_fork = (i + 1) % data->philo_nb;
		data->philo[i].data = data;
		data->philo[i].start_time.tv_sec = 0;
		data->philo[i].start_time.tv_usec = 0;
		data->philo[i].current_time.tv_sec = 0;
		data->philo[i].current_time.tv_usec = 0;
		i++;
	}
}

void	start_routine(t_data *data, pthread_t *threads)
{
	int	i;

	i = 0;
	gettimeofday(&data->start_pg, NULL);
	while (i < data->philo_nb)
	{
		pthread_create(&threads[i], NULL, philo_routine, (void*)&data->philo[i]);
		printf("%sCreation du Philosophe %d%s\n", GREEN, data->philo[i].thread_id, NC);
		usleep(1000);
		i++;
	}
}

void	waiting_treads(t_data *data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_join(threads[i], NULL);
		printf("%sUnion du Philosophe %d%s\n", GREEN, data->philo[i].thread_id, NC);
		i++;
	}
}

void	free_philo(t_data *data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex);
	free(data->forks);
	free(data->philo);
	free(threads);
}
