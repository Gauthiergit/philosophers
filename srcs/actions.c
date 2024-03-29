/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:37:41 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/29 15:18:20 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	taking_forks(t_philo *philo)
{
	if (philo->thread_id % 2 == 0)
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	else
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	if (!check_if_stop(philo))
		ft_display(philo, "has taken a fork", YELLOW);
	if (philo->thread_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
/* 		if (pthread_mutex_lock(&philo->data->forks[philo->left_fork]) != 0)
		{
			pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
			return (1);
		} */
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
/* 		if (pthread_mutex_lock(&philo->data->forks[philo->right_fork]) != 0)
		{
			pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
			return (1);
		} */
	}
	if (!check_if_stop(philo))
		ft_display(philo, "has taken a fork", YELLOW);
	return (0);
}

void	eating(t_philo *philo)
{
	ft_display(philo, "is eating", YELLOW);
	pthread_mutex_lock(&philo->data->time);
	gettimeofday(&philo->start_time, NULL);
	pthread_mutex_unlock(&philo->data->time);
	usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->eat);
	if (philo->data->eat_nb != -1)
		philo->count_eat--;
	pthread_mutex_unlock(&philo->data->eat);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

void	sleeping(t_philo *philo)
{
	ft_display(philo, "is sleeping", YELLOW);
	usleep(philo->data->time_to_sleep);
}
