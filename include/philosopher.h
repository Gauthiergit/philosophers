/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:41:00 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/19 17:40:29 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define RED	"\e[31m"
#define GREEN	"\e[32m"
#define NC	"\e[0m"
#define YELLOW	"\e[33m"

typedef	struct s_data
{
	pthread_mutex_t	*forks;
	int				philo_nb;
	long int		time_to_die;
	long int		time_to_sleep;
	long int		time_to_eat;
}	t_data;

typedef	struct s_philo
{
	int			thread_id;
	t_data		*data;
}	t_philo;

/* typedef struct	s_data
{
	long int	philo_nb;
	long int	time_to_die;
	long int	time_to_sleep;
	long int	time_to_eat;
	t_philo		*lst_philo;
	t_fork		*lst_fork;
}	t_data; */

/* srcs */
/* philosopher.c */
void				*philo_routine(void *infos);

/* error.c */
void				check_error(int argc, char **argv, t_data *data);

/* utils.c */
unsigned long int	ft_atoi(const char *str);
void				init_mutex(t_data *data);
void				init_philo(t_data *data, t_philo *philo, pthread_t *threads);
void				waiting_treads(t_philo *philo, pthread_t *threads);
void				free_philo(t_philo *philo, pthread_t *threads);

#endif