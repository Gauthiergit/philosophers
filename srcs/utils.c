/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:41:11 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/27 16:09:38 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

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

void	free_philo(t_data *data, pthread_t *threads)
{
	unsigned int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->display);
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->time);
	pthread_mutex_destroy(&data->eat);
	free(data->forks);
	free(data->philo);
	free(threads);
}

void	ft_display(t_philo *philo, const char *str, char *color)
{
	pthread_mutex_lock(&philo->data->display);
	printf("%s[%lld] Philosopher %d %s%s\n",
		color, cur_time(philo), philo->thread_id, str, NC);
	pthread_mutex_unlock(&philo->data->display);
}

long long	timeval_diff(struct timeval *start, struct timeval *end)
{
	long long	res;

	res = (end->tv_sec - start->tv_sec) * 1000000LL;
	res += (end->tv_usec - start->tv_usec);
	return (res);
}

long long	cur_time(t_philo *philo)
{
	long long	cur_usec;
	long long	cur_millisec;

	cur_usec = 0;
	cur_millisec = 0;
	gettimeofday(&philo->current_time, NULL);
	cur_usec = timeval_diff(&philo->data->start_pg, &philo->current_time);
	cur_millisec = cur_usec / 1000;
	return (cur_millisec);
}
