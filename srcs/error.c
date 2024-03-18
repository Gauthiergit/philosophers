/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:18:40 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/18 19:01:03 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	check_cara(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

void	check_error(int argc, char **argv)
{
	int	i;

	/* if (argc < 5)
	{
		printf("You have to use at least 5 arguments\n");
		exit(1);
	} */
	i = 1;
	while (i < argc)
	{
		if (check_cara(argv[i]))
		{
			printf("Program accept only numeric arguments\n");
			exit(1);
		}
		i++;
	}
}

void	ft_clear_philo(t_philo **lst)
{
	t_philo	*current;
	t_philo	*futur;

	current = *lst;
	if (!lst || !(*lst))
		return ;
	while (current->next != *lst)
	{
		futur = current->next;
		free(current);
		current = futur;
	}
	free(current);
	*lst = NULL;
}

void	ft_clear_fork(t_fork **lst)
{
	t_fork	*current;
	t_fork	*futur;

	current = *lst;
	if (!lst || !(*lst))
		return ;
	while (current->next != *lst)
	{
		futur = current->next;
		pthread_mutex_destroy(&current->lock);
		free(current);
		current = futur;
	}
	free(current);
	*lst = NULL;
}
