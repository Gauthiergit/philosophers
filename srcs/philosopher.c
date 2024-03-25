/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:40:43 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/25 17:50:03 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philosopher.h"

int	taking_forks(t_philo *philo)
{
	if (philo->thread_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		if (!check_if_dead(philo))
		{
			pthread_mutex_lock(&philo->data->display);
			printf("%s[%lld] Philosopher %d takes fork %d%s\n", YELLOW, cur_time(philo), philo->thread_id, philo->right_fork, NC);
			pthread_mutex_unlock(&philo->data->display);
		}
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		if (!check_if_dead(philo))
		{
			pthread_mutex_lock(&philo->data->display);
			printf("%s[%lld] Philosopher %d takes fork %d%s\n", YELLOW, cur_time(philo), philo->thread_id, philo->left_fork, NC);
			pthread_mutex_unlock(&philo->data->display);
		}
	}
	if (philo->thread_id % 2 == 0)
	{
		if (pthread_mutex_lock(&philo->data->forks[philo->left_fork]) != 0)
			return (pthread_mutex_unlock(&philo->data->forks[philo->right_fork]), 1);
		if (!check_if_dead(philo))
		{
			pthread_mutex_lock(&philo->data->display);
			printf("%s[%lld] Philosopher %d takes fork %d%s\n", YELLOW, cur_time(philo), philo->thread_id, philo->left_fork, NC);
			pthread_mutex_unlock(&philo->data->display);
		}
	}
	else
	{
		if (pthread_mutex_lock(&philo->data->forks[philo->right_fork]) != 0)
			return (pthread_mutex_unlock(&philo->data->forks[philo->left_fork]), 1);
		if (!check_if_dead(philo))
		{
			pthread_mutex_lock(&philo->data->display);
			printf("%s[%lld] Philosopher %d takes fork %d%s\n", YELLOW, cur_time(philo), philo->thread_id, philo->right_fork, NC);
			pthread_mutex_unlock(&philo->data->display);
		}
	}
	return (0);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->display);
	printf("%s[%lld] Philosopher %d start eating%s\n", YELLOW, cur_time(philo), philo->thread_id, NC);
	pthread_mutex_unlock(&philo->data->display);
	pthread_mutex_lock(&philo->data->time);
	gettimeofday(&philo->start_time, NULL);
	pthread_mutex_unlock(&philo->data->time);
	usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->display);
	printf("%s[%lld] Philosopher %d start sleeping%s\n", YELLOW, cur_time(philo), philo->thread_id, NC);
	pthread_mutex_unlock(&philo->data->display);
	usleep(philo->data->time_to_sleep);
}

void	*philo_routine(void *infos)
{
	t_philo			*philo;
	
	philo = (t_philo*)infos;
	while (!check_if_dead(philo))
	{
		if (check_if_dead(philo))
			return (NULL);
		taking_forks(philo);
		if (check_if_dead(philo))
		{
			pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
			return (NULL);
		}
		eating(philo);
		if (check_if_dead(philo))
			return (NULL);
		sleeping(philo);
		if (check_if_dead(philo))
			return (NULL);
		pthread_mutex_lock(&philo->data->display);
		printf("%s[%lld] Philosopher %d is thinking%s\n", YELLOW, cur_time(philo), philo->thread_id, NC);
		pthread_mutex_unlock(&philo->data->display);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	*threads;

	check_error(argc, argv, &data);
	threads = malloc(data.philo_nb * sizeof(pthread_t));
	if (!threads)
		return (1);
	start_routine(&data, threads);
	philo_monitoring(&data);
	waiting_treads(&data, threads);
	free_philo(&data, threads);
	return (0);
}

// accélérer l'affichage de la mort
// gerer le nombres de fois ou le philo mange 