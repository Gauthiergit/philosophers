/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:41:00 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/15 18:15:21 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define RED	"\e[31m"
#define GREEN	"\e[32m"
#define NC	"\e[0m"
#define YELLOW	"\e[33m"

typedef	struct s_philo
{
	pthread_t		tid;
	int				nb;
	struct s_philo	*next;
}	t_philo;

typedef	struct s_fork
{
	pthread_mutex_t	lock;
	int				nb;
}	t_fork;

/* srcs */

/* error.c */
void	check_error(int argc, char **argv);

/* utils.c */
int		ft_atoi(const char *str);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo	*ft_lstnew(int nb);

#endif