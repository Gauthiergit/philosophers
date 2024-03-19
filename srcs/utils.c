/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:41:11 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/19 17:44:02 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philosopher.h"

unsigned long int	ft_atoi(const char *str)
{
	unsigned long int	i;
	unsigned long int	result;

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
}

void	init_philo(t_data *data, t_philo *philo, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		philo[i].thread_id = i;
		philo[i].data = data;
		pthread_create(&threads[i], NULL, philo_routine, (void*)&philo[i]);
		printf("%sCreation du Philosophe %d%s\n", GREEN, philo[i].thread_id, NC);
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
		pthread_mutex_destroy(philo[i].data->forks);
		i++;
	}
	free(philo);
	free(threads);
}
/* void	ft_add_back_p(t_philo **lst, t_philo *new)
{
	t_philo	*current;	

	current = NULL;
	if (!new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
} */

/* void	ft_add_back_f(t_fork **lst, t_fork *new)
{
	t_fork	*current;

	current = NULL;
	if (!new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
} */

/* t_philo	*ft_new_philo(int nb)
{
	t_philo	*new;

	new = (t_philo *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->custom_id = nb;
	pthread_mutex_init(&new->lock, NULL);
	new->next = NULL;
	return (new);
} */

/* t_fork	*ft_new_fork(int nb)
{
	t_fork	*new;

	new = (t_fork *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	pthread_mutex_init(&new->lock, NULL);
	new->custom_id = nb;
	new->next = NULL;
	return (new);
} */
