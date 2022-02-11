/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 20:31:49 by sel-mars          #+#    #+#             */
/*   Updated: 2022/01/31 20:31:49 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_cop(t_philo **philo)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < (*philo)[i].param.nb_philo
			&& (*philo)[0].in_routine == (*philo)[i].param.nb_philo
			&& (*philo)[i].current_time)
		{
			pthread_mutex_lock((*philo)[i].alive_ptr);
			if ((*philo)[0].nb_full_eat == (*philo)[i].param.nb_philo)
			{
				pthread_mutex_lock((*philo)[i].print_ptr);
				return (ft_destroy_all(philo));
			}
			ft_get_time(&(*philo)[i].elapsed_time, (*philo)[i].current_time);
			if ((*philo)[i].elapsed_time > (*philo)[i].param.t_die)
			{
				ft_print_message(&(*philo)[i], 5);
				return (ft_destroy_all(philo));
			}
			pthread_mutex_unlock((*philo)[i++].alive_ptr);
		}
	}
	return (0);
}

int	ft_philo(int ac, char **av)
{
	t_param	param;
	t_philo	*philo;

	ft_get_time(&(param.start_time), 0);
	if (ft_parse(ac, av, &param))
		return (1);
	philo = ft_create_philos(param);
	if (!philo || ft_create_threads(param, &philo))
		return (ft_puterror_ret_1("Error creating philosophers\n"));
	if (ft_into_threads(param, &philo))
		return (ft_puterror_ret_1("Error dealing with threads\n"));
	return (0);
}
