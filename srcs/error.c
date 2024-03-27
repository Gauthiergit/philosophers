/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:18:40 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/27 17:03:33 by gpeyre           ###   ########.fr       */
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

void	check_sup_zero(t_data *data)
{
	if (!data->philo_nb || !data->time_to_die || !data->time_to_sleep
		|| !data->time_to_eat)
	{
		printf("Numbers must be greater than zero\n");
		exit(1);
	}
}

void	check_error(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: At least 4 arguments and no more than 5.\n");
		exit(1);
	}
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
