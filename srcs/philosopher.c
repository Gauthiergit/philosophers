/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:40:43 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/15 18:39:58 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philosopher.h"

void	init_philo(int philo_nb, t_philo **lst_philo)
{
	int	i;
	t_philo *new;

	i = 1;
	while (i < philo_nb)
	{
		new = ft_lstnew(i);
		ft_lstadd_back(lst_philo, new);
		i++;
	}
	new = ft_lstnew(i);
	new->next = *lst_philo;
	ft_lstadd_back(lst_philo, new);
}

int	main(int argc, char **argv)
{
	t_philo *lst_philo;
	int		philo_nb;

	lst_philo = NULL;
	philo_nb = ft_atoi(argv[1]);
	check_error(argc, argv);
	init_philo(philo_nb, &lst_philo);
	return (0);
}
	/* int i = 0;
	while (i < philo_nb + 1)
	{
		printf("Philosophe %d\n", lst_philo->nb);
		printf("Son next : Philosophe %d\n", lst_philo->next->nb);
		i++;
		lst_philo = lst_philo->next;
	} */