/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:41:11 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/18 19:12:18 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philosopher.h"

long int	ft_atoi(const char *str)
{
	long int	i;
	long int	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result);
}

void	ft_add_back_p(t_philo **lst, t_philo *new)
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
}

void	ft_add_back_f(t_fork **lst, t_fork *new)
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
}

t_philo	*ft_new_philo(int nb)
{
	t_philo	*new;

	new = (t_philo *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->custom_id = nb;
	new->next = NULL;
	return (new);
}

t_fork	*ft_new_fork(int nb)
{
	t_fork	*new;

	new = (t_fork *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	pthread_mutex_init(&new->lock, NULL);
	new->custom_id = nb;
	new->next = NULL;
	return (new);
}
