/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:36:04 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/29 15:19:06 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	*philo_routine(void *infos)
{
	t_philo	*philo;

	philo = (t_philo *)infos;
	if (philo->thread_id % 2 == 0)
		usleep(15000);
	while (!check_if_stop(philo))
	{
		if (check_if_stop(philo))
			return (NULL);
		taking_forks(philo);
		if (check_if_stop(philo))
		{
			pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
			return (NULL);
		}
		eating(philo);
		if (check_if_stop(philo))
			return (NULL);
		sleeping(philo);
		if (check_if_stop(philo))
			return (NULL);
		ft_display(philo, "is thinking", YELLOW);
	}
	return (NULL);
}

void	start_routine(t_data *data, pthread_t *threads)
{
	unsigned int	i;

	i = 0;
	gettimeofday(&data->start_pg, NULL);
	while (i < data->philo_nb)
	{
		pthread_create(&threads[i], NULL, philo_routine,
			(void*)&data->philo[i]);
		i++;
	}
}

void	waiting_treads(t_data *data, pthread_t *threads)
{
	unsigned int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
