/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:40:43 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/20 19:32:40 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philosopher.h"

void	check_if_dead(t_philo *philo)
{
	long long int	elapsed_time;

	elapsed_time = 0;
	if (philo->start_time.tv_sec)
	{
		gettimeofday(&philo->current_time, NULL);
		elapsed_time = timeval_diff(&philo->start_time, &philo->current_time);
		if (elapsed_time > philo->data->time_to_die)
		{
			printf("%s[%lld] Philosopher [%d] is dead%s\n", RED, cur_time(philo), philo->thread_id, NC);
			philo->data->so_dead = 1;
		}
		philo->start_time.tv_sec = 0;
		philo->start_time.tv_usec = 0;
	}
}

void	eating(t_philo *philo, int l_fork, int r_fork)
{
	pthread_mutex_lock(&philo->data->check_dead);
	check_if_dead(philo);
	if (philo->data->so_dead)
		return ;
	pthread_mutex_unlock(&philo->data->check_dead);
	printf("%s[%lld] Philosopher %d takes fork %d%s\n", YELLOW, cur_time(philo), philo->thread_id, l_fork, NC);
	printf("%s[%lld] Philosopher %d takes fork %d%s\n", YELLOW, cur_time(philo), philo->thread_id, r_fork, NC);
	printf("%s[%lld] Philosopher %d start eating%s\n", YELLOW, cur_time(philo), philo->thread_id, NC);
	usleep(philo->data->time_to_eat);
	printf("%s[%lld] Philosopher %d returns fork %d%s\n", YELLOW, cur_time(philo), philo->thread_id, r_fork, NC);
	printf("%s[%lld] Philosopher %d returns fork %d%s\n", YELLOW, cur_time(philo), philo->thread_id, l_fork, NC);
	gettimeofday(&philo->start_time, NULL);
}

void	*philo_routine(void *infos)
{
	t_philo			*philo;
	int				left_fork;
	int				right_fork;
	
	philo = (t_philo*)infos;
	while (!philo->data->so_dead)
	{
		left_fork = philo->thread_id;
		right_fork = (philo->thread_id + 1) % philo->data->philo_nb;
		pthread_mutex_lock(&philo->data->forks[left_fork]);
		pthread_mutex_lock(&philo->data->forks[right_fork]);
		eating(philo, left_fork, right_fork);
		if (philo->data->so_dead)
			return (NULL);
		pthread_mutex_unlock(&philo->data->forks[right_fork]);
		pthread_mutex_unlock(&philo->data->forks[left_fork]);
		pthread_mutex_lock(&philo->data->display);
		gettimeofday(&philo->current_time, NULL);
		printf("%s[%lld] Philosopher %d start sleeping%s\n", YELLOW, cur_time(philo), philo->thread_id, NC);
		usleep(philo->data->time_to_sleep);
		pthread_mutex_unlock(&philo->data->display);
		pthread_mutex_lock(&philo->data->display);
		gettimeofday(&philo->current_time, NULL);
		printf("%s[%lld] Philosopher %d is thinking%s\n", YELLOW, cur_time(philo), philo->thread_id, NC);
		printf("%s[%lld] Philosopher %d finish is routine%s\n", GREEN, cur_time(philo), philo->thread_id, NC);
		pthread_mutex_unlock(&philo->data->display);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	*threads;
	t_philo 	*philo;

	check_error(argc, argv, &data);
	threads = malloc(data.philo_nb * sizeof(pthread_t));
	if (!threads)
		return (1);
	philo = malloc(data.philo_nb * sizeof(t_philo));
	if (!philo)
		return (1);
	init_mutex(&data);
	init_philo(&data, philo, threads);
/* 	if (philo->data->so_dead)
	{
		printf("[%lld] Finish\n", cur_time(philo));
		free_philo(philo, threads);
		return (1);
	} */
	waiting_treads(philo, threads);
	free_philo(philo, threads);
	return (0);
}

//rajouter un mutex à l'interieur de la fonction eating