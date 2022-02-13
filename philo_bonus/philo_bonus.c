/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 20:31:49 by sel-mars          #+#    #+#             */
/*   Updated: 2022/01/31 20:31:49 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_check(t_philo **philo)
{
	int	i;

	i = -1;
	waitpid(-1, NULL, 0);
	ft_end(philo, (*philo)[0].common.nb_philo);
}

int	ft_philo_bonus(int ac, char **av)
{
	t_common	common;
	t_philo		*philo;

	common.nb_eat = 0;
	if (ft_parse(ac, av, &common))
		return (1);
	philo = ft_create_philos(&common);
	if (!philo)
		return (ft_puterror_ret_1("Error creating philos\n"));
	if (ft_create_philo_processes(&philo))
		return (ft_puterror_ret_1("Error creating forks\n"));
	ft_check(&philo);
	return (0);
}
