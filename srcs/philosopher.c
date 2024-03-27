/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:40:43 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/27 16:07:21 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	*threads;

	check_error(argc, argv);
	init_data(&data, argv);
	threads = malloc(data.philo_nb * sizeof(pthread_t));
	if (!threads)
		return (1);
	start_routine(&data, threads);
	philo_monitoring(&data);
	waiting_treads(&data, threads);
	free_philo(&data, threads);
	return (0);
}
