/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:41:00 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/22 18:31:50 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define RED	"\e[31m"
#define GREEN	"\e[32m"
#define NC	"\e[0m"
#define YELLOW	"\e[33m"

typedef	struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex;
	int				philo_nb;
	long long int	time_to_die;
	long long int	time_to_sleep;
	long long int	time_to_eat;
	int				so_dead;
	int				dead_id;
	struct s_philo	*philo;
	struct timeval	start_pg;
}	t_data;

typedef	struct s_philo
{
	int				thread_id;
	int				right_fork;
	int				left_fork;
	struct timeval	start_time;
	struct timeval	current_time;
	t_data			*data;
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

/* utils_2.c */
void		*philo_monitoring(t_data *data, pthread_t *threads);
void		check_last_meal(t_philo *philo);
long long	timeval_diff(struct timeval *start, struct timeval *end);
long long	cur_time(t_philo *philo);
int			check_if_dead(t_philo *philo);
void		detach_threads(pthread_t *threads, t_data *data);

/* utils.c */
long long int	ft_atoi(const char *str);
void			init_mutex(t_data *data);
void			init_philo(t_data *data);
void			start_routine(t_data *data, pthread_t *threads);
void			waiting_treads(t_data *data, pthread_t *threads);
void			free_philo(t_data *data, pthread_t *threads);

#endif