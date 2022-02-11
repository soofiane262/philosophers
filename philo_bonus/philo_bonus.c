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

int	ft_philo_bonus(int ac, char **av)
{
	t_param	*param;

	param = (t_param *)malloc(sizeof(t_param));
	if (ft_parse(ac, av, &param))
		return (1);
	sem_unlink("/forks");
	param->sem = sem_open("/forks", O_CREAT, 777, param->nb_philo);
	printf("nb_philo	:	%d\nt_die		:	%d\nt_eat		:	%d\nt_sleep		:	%d\n", param->nb_philo, param->t_die, param->t_eat, param->t_sleep);
	sem_close(param->sem);
	return (0);
}
