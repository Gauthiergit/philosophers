/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:09:52 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/22 18:32:36 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philosopher.h"

long long	timeval_diff(struct timeval *start, struct timeval *end)
{
	return (end->tv_sec - start->tv_sec) * 1000000LL + (end->tv_usec - start->tv_usec);
}

long long	cur_time(t_philo *philo)
{
	long long	cur_usec;
	long long	cur_millisec;

	cur_usec = 0;
	cur_millisec = 0;
	gettimeofday(&philo->current_time, NULL);
	cur_usec = timeval_diff(&philo->data->start_pg, &philo->current_time);
	cur_millisec = cur_usec  / 1000;
	return (cur_millisec);
}

void	detach_threads(pthread_t *threads, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_detach(threads[i]);
		i++;
	}
}

void	check_last_meal(t_philo *philo)
{
	long long int	elapsed_time;

	elapsed_time = 0;
	if (philo->start_time.tv_sec)
	{
		gettimeofday(&philo->current_time, NULL);
		elapsed_time = timeval_diff(&philo->start_time, &philo->current_time);
		if (elapsed_time > philo->data->time_to_die)
		{
			printf("%s[%lld] Philosopher %d is dead%s\n", RED, cur_time(philo), philo->thread_id, NC);
			philo->data->so_dead = 1;
			philo->data->dead_id = philo->thread_id;

		}
	}
}

void	*philo_monitoring(t_data *data, pthread_t *threads)
{
	int		i;

	while (1)
	{
		i = 0;
		while (i < data->philo_nb)
		{
			pthread_mutex_lock(&data->mutex);
			check_last_meal(&data->philo[i]);
			if (data->so_dead)
			{
				detach_threads(threads, data);
				pthread_mutex_unlock(&data->mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->mutex);
			i++;
		}
	}
}

int	check_if_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex);
	if (philo->data->so_dead)
	{
		pthread_mutex_unlock(&philo->data->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex);
	return (0);
}
