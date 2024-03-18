/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:41:00 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/18 18:22:45 by gpeyre           ###   ########.fr       */
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

typedef	struct s_philo
{
	pthread_t		tid;
	int				custom_id;
	struct s_philo	*next;
}	t_philo;

typedef	struct s_fork
{
	pthread_mutex_t	lock;
	int				custom_id;
	struct s_fork	*next;
}	t_fork;

typedef struct	s_data
{
	long int	philo_nb;
	long int	time_to_die;
	long int	time_to_sleep;
	long int	time_to_eat;
	t_philo		*lst_philo;
	t_fork		*lst_fork;
}	t_data;

/* srcs */

/* error.c */
void			check_error(int argc, char **argv);
void			ft_clear_philo(t_philo **lst);
void			ft_clear_fork(t_fork **lst);

/* utils.c */
long int	ft_atoi(const char *str);
void			ft_add_back_f(t_fork **lst, t_fork *new);
void			ft_add_back_p(t_philo **lst, t_philo *new);
t_philo			*ft_new_philo(int nb);
t_fork			*ft_new_fork(int nb);

#endif