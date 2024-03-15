/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:18:40 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/15 17:51:30 by gpeyre           ###   ########.fr       */
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

	/* if (argc < 6)
	{
		printf("You have to use 5 arguments\n");
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
