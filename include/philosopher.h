/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:41:00 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/29 11:17:39 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define NC	"\e[0m"
# define YELLOW	"\e[33m"

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	display;
	pthread_mutex_t	dead;
	pthread_mutex_t	time;
	pthread_mutex_t	eat;
	unsigned int	philo_nb;
	unsigned int	finish;
	int				eat_nb;
	long long int	time_to_die;
	long long int	time_to_sleep;
	long long int	time_to_eat;
	int				so_dead;
	struct s_philo	*philo;
	struct timeval	start_pg;
}	t_data;

typedef struct s_philo
{
	int				thread_id;
	int				right_fork;
	int				left_fork;
	int				count_eat;
	int				full;
	struct timeval	start_time;
	struct timeval	current_time;
	t_data			*data;
}	t_philo;

/* srcs */
/* actions.c */
int				taking_forks(t_philo *philo);
void			eating(t_philo *philo);
void			sleeping(t_philo *philo);

/* error.c */
void			check_error(int argc, char **argv);
int				check_cara(char *str);
void			check_sup_zero(t_data *data);

/* init.c */
void			init_data(t_data *data, char **argv);
void			init_mutex(t_data *data);
void			init_philo(t_data *data);

/* monitoring.c */
void			*philo_monitoring(t_data *data);
void			check_last_meal(t_philo *philo);
int				check_if_stop(t_philo *philo);
void			check_eat_nb(t_philo *philo);

/* routine.c */
void			*philo_routine(void *infos);
void			start_routine(t_data *data, pthread_t *threads);
void			waiting_treads(t_data *data, pthread_t *threads);

/* utils.c */
long long		cur_time(t_philo *philo);
long long		timeval_diff(struct timeval *start, struct timeval *end);
long long int	ft_atoi(const char *str);
void			free_philo(t_data *data, pthread_t *threads);
void			ft_display(t_philo *philo, const char *str, char *color);

#endif