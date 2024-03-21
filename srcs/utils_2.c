/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:09:52 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/21 16:44:01 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philosopher.h"

long long	timeval_diff(struct timeval *start, struct timeval *end)
{
	return (end->tv_sec - start->tv_sec) * 1000000LL + (end->tv_usec - start->tv_usec);
}

long long	cur_time(t_philo *philo)
{
	long long	cur_usec;
	long long	cur_millisec;

	cur_usec = 0;
	cur_millisec = 0;
	gettimeofday(&philo->current_time, NULL);
	cur_usec = timeval_diff(&philo->data->start_pg, &philo->current_time);
	cur_millisec = cur_usec  / 1000;
	return (cur_millisec);
}
