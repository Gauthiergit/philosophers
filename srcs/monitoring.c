/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:39:25 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/27 15:40:14 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	check_last_meal(t_philo *philo)
{
	long long int	elapsed_time;

	elapsed_time = 0;
	pthread_mutex_lock(&philo->data->time);
	if (philo->start_time.tv_sec)
	{
		gettimeofday(&philo->current_time, NULL);
		elapsed_time = timeval_diff(&philo->start_time, &philo->current_time);
		if (elapsed_time > philo->data->time_to_die)
		{
			ft_display(philo, "died", RED);
			philo->data->so_dead = 1;
		}
	}
	pthread_mutex_unlock(&philo->data->time);
}

void	*philo_monitoring(t_data *data)
{
	unsigned int	i;

	while (1)
	{
		i = 0;
		while (i < data->philo_nb)
		{
			pthread_mutex_lock(&data->eat);
			if (data->finish)
			{
				pthread_mutex_unlock(&data->eat);
				return (NULL);
			}
			pthread_mutex_unlock(&data->eat);
			pthread_mutex_lock(&data->dead);
			check_last_meal(&data->philo[i]);
			if (data->so_dead)
			{
				pthread_mutex_unlock(&data->dead);
				return (NULL);
			}
			pthread_mutex_unlock(&data->dead);
			i++;
		}
	}
}

void	check_eat_nb(t_philo *philo)
{
	if (philo->count_eat == 0)
		philo->data->finish++;
	if (philo->data->finish == philo->data->philo_nb)
	{
		pthread_mutex_lock(&philo->data->display);
		printf("%sPhilo have finished eating !!%s\n", GREEN, NC);
		pthread_mutex_unlock(&philo->data->display);
	}
}

int	check_if_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead);
	if (philo->data->so_dead)
	{
		pthread_mutex_unlock(&philo->data->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead);
	pthread_mutex_lock(&philo->data->eat);
	if (philo->data->eat_nb)
	{
		if (philo->count_eat == 0)
		{
			pthread_mutex_unlock(&philo->data->eat);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->data->eat);
	return (0);
}