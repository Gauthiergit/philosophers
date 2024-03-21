/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:41:11 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/21 16:04:39 by gpeyre           ###   ########.fr       */
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
	pthread_mutex_init(&data->eating, NULL);
	pthread_mutex_init(&data->check_dead, NULL);
	pthread_mutex_init(&data->sleeping, NULL);
	pthread_mutex_init(&data->thinking, NULL);
}

void	init_philo(t_data *data, t_philo *philo, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		philo[i].thread_id = i;
		philo[i].data = data;
		philo[i].start_time.tv_sec = 0;
		philo[i].start_time.tv_usec = 0;
		philo[i].current_time.tv_sec = 0;
		philo[i].current_time.tv_usec = 0;
		pthread_create(&threads[i], NULL, philo_routine, (void*)&philo[i]);
		printf("%sCreation du Philosophe %d%s\n", GREEN, philo[i].thread_id, NC);
		usleep(1000);
		i++;
	}
}

void	waiting_treads(t_philo *philo, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_nb)
	{
		pthread_join(threads[i], NULL);
		printf("%sUnion du Philosophe %d%s\n", GREEN, philo[i].thread_id, NC);
		i++;
	}
}

void	free_philo(t_philo *philo, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_nb)
	{
		pthread_mutex_destroy(&philo->data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->data->check_dead);
	pthread_mutex_destroy(&philo->data->eating);
	pthread_mutex_destroy(&philo->data->sleeping);
	pthread_mutex_destroy(&philo->data->thinking);
	free(philo->data->forks);
	free(philo);
	free(threads);
}
