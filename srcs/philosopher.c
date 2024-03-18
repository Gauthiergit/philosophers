/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:40:43 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/18 19:16:59 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philosopher.h"

void	init_philo(int philo_nb, t_philo **lst_philo, t_fork **lst_fork)
{
	int	i;
	t_philo *new_philo;
	t_fork	*new_fork;

	i = 1;
	while (i < philo_nb)
	{
		new_philo = ft_new_philo(i);
		new_fork = ft_new_fork(i);
		ft_add_back_p(lst_philo, new_philo);
		ft_add_back_f(lst_fork, new_fork);
		i++;
	}
	new_philo = ft_new_philo(i);
	new_fork = ft_new_fork(i);
	new_philo->next = *lst_philo;
	new_fork->next = *lst_fork;
	ft_add_back_p(lst_philo, new_philo);
	ft_add_back_f(lst_fork, new_fork);
}

void	init_data(t_data *data, char **argv)
{
	data->philo_nb = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]) * 1000;
	data->time_to_eat = ft_atoi(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi(argv[4]) * 1000;
	data->lst_philo = NULL;
	data->lst_fork = NULL;
	init_philo(data->philo_nb, &data->lst_philo, &data->lst_fork);
}

void	*philo_routine(void *infos)
{
	t_fork	*temp;
	t_data	*data;

	data = (t_data *)infos;
	temp = data->lst_fork;
	pthread_mutex_lock(&data->lst_fork->lock);
	printf("%sPhilosopher [%d] takes fork [%d]%s\n", YELLOW, data->lst_philo->custom_id, data->lst_fork->custom_id, NC);
	data->lst_fork = data->lst_fork->next;
	pthread_mutex_lock(&data->lst_fork->lock);
	printf("%sPhilosopher [%d] takes fork [%d]%s\n", YELLOW, data->lst_philo->custom_id, data->lst_fork->custom_id, NC);
	printf("%sPhilosopher [%d] start eating%s\n", YELLOW, data->lst_philo->custom_id, NC);
	usleep(data->time_to_eat);
	printf("%sPhilosopher [%d] returns fork [%d]%s\n", YELLOW, data->lst_philo->custom_id, data->lst_fork->custom_id, NC);
	pthread_mutex_unlock(&data->lst_fork->lock);
	data->lst_fork = temp;
	printf("%sPhilosopher [%d] returns fork [%d]%s\n", YELLOW, data->lst_philo->custom_id, data->lst_fork->custom_id, NC);
	pthread_mutex_unlock(&data->lst_fork->lock);
	printf("%sPhilosopher [%d] start sleeping%s\n", YELLOW, data->lst_philo->custom_id, NC);
	usleep(data->time_to_sleep);
	printf("%sPhilosopher [%d] is thinking%s\n", YELLOW, data->lst_philo->custom_id, NC);
	data->lst_fork = data->lst_fork->next;
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*cur;

	check_error(argc, argv);
	init_data(&data, argv);
	cur = data.lst_philo;
	while (cur->next != data.lst_philo)
	{
		pthread_create(&cur->tid, NULL, philo_routine, &data);
		printf("%sCreation du Philosophe %d%s\n", GREEN, cur->custom_id, NC);
		cur = cur->next;
	}
	pthread_create(&cur->tid, NULL, philo_routine, &data);
	printf("%sCreation du Philosophe %d%s\n", GREEN, cur->custom_id, NC);
	cur = cur->next;
	while (cur->next != data.lst_philo)
	{
		pthread_join(cur->tid, NULL);
		printf("%sUnion du Philosophe %d%s\n", GREEN, cur->custom_id, NC);
		cur = cur->next;
	}
	pthread_join(cur->tid, NULL);
	printf("%sUnion du Philosophe %d%s\n", GREEN, cur->custom_id, NC);
	ft_clear_philo(&data.lst_philo);
	ft_clear_fork(&data.lst_fork);
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