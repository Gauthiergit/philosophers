/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:40:43 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/19 17:36:43 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philosopher.h"

/* void	init_philo(int philo_nb, t_philo **lst_philo)
{
	int	i;
	t_philo *new_philo;
	// t_fork	*new_fork;

	i = 1;
	while (i < philo_nb)
	{
		new_philo = ft_new_philo(i);
		// new_fork = ft_new_fork(i);
		ft_add_back_p(lst_philo, new_philo);
		// ft_add_back_f(lst_fork, new_fork);
		i++;
	}
	new_philo = ft_new_philo(i);
	// new_fork = ft_new_fork(i);
	new_philo->next = *lst_philo;
	// new_fork->next = *lst_fork;
	ft_add_back_p(lst_philo, new_philo);
	// ft_add_back_f(lst_fork, new_fork);
} */

void	*philo_routine(void *infos)
{
	t_philo	*philo;
	int		left_fork;
	int		right_fork;
	// pthread_t	tid;

	philo = (t_philo*)infos;
	left_fork = philo->thread_id;
	right_fork = (philo->thread_id + 1) % philo->data->philo_nb;
	// tid = pthread_self();
	pthread_mutex_lock(&philo->data->forks[left_fork]);
	printf("%sPhilosopher [%d] takes fork [%d]%s\n", YELLOW, philo->thread_id, left_fork, NC);
	pthread_mutex_lock(&philo->data->forks[right_fork]);
	printf("%sPhilosopher [%d] takes fork [%d]%s\n", YELLOW, philo->thread_id, right_fork, NC);
	printf("%sPhilosopher [%d] start eating%s\n", YELLOW, philo->thread_id, NC);
	usleep(philo->data->time_to_eat);
	printf("%sPhilosopher [%d] returns fork [%d]%s\n", YELLOW, philo->thread_id, right_fork, NC);
	pthread_mutex_unlock(&philo->data->forks[right_fork]);
	printf("%sPhilosopher [%d] returns fork [%d]%s\n", YELLOW, philo->thread_id, left_fork, NC);
	pthread_mutex_unlock(&philo->data->forks[left_fork]);
	printf("%sPhilosopher [%d] start sleeping%s\n", YELLOW, philo->thread_id, NC);
	usleep(philo->data->time_to_sleep);
	printf("%sPhilosopher [%d] is thinking%s\n", YELLOW, philo->thread_id, NC);
	printf("%sPhilosopher [%d] finish is routine%s\n", GREEN, philo->thread_id, NC);
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
	waiting_treads(philo, threads);
	free_philo(philo, threads);
	return (0);
}

/* 	int i = 0;
	while (i < philo_nb + 1)
	{
		printf("Philosophe %d\n", lst_philo->nb);
		printf("Son next : Philosophe %d\n", lst_philo->next->nb);
		i++;
		lst_philo = lst_philo->next;
	}
	printf("----------------------------------\n");
	i = 0;
	while (i < philo_nb + 1)
	{
		printf("Fourchette %d\n", lst_fork->nb);
		printf("Son next : Fourchette %d\n", lst_fork->next->nb);
		i++;
		lst_fork = lst_fork->next;
	} */