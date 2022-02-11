/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_03_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:52:05 by sel-mars          #+#    #+#             */
/*   Updated: 2022/02/02 18:52:07 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_destroy_all(t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < (*philo)[0].param.nb_philo)
	{
		pthread_detach((*philo)[i].philo_id);
		pthread_mutex_destroy(&((*philo)[i].fork_r));
	}
	pthread_mutex_destroy((*philo)[0].alive_ptr);
	return (0);
}

int	ft_into_threads(t_param param, t_philo **philo)
{
	int			i;

	i = -1;
	while (++i < param.nb_philo)
		if (pthread_create(&(*philo)[i].philo_id, 0, ft_life_routine,
			(void *)&(*philo)[i]))
			return (1);
	ft_cop(philo);
	return (0);
}

int	ft_cop(t_philo **philo)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i >= 0 && i < (*philo)[i].param.nb_philo
			&& (*philo)[0].in_routine == (*philo)[i].param.nb_philo)
		{
			pthread_mutex_lock((*philo)[i].alive_ptr);
			if ((*philo)[0].nb_full_eat == (*philo)[i].param.nb_philo)
			{
				pthread_mutex_lock((*philo)[i].print_ptr);
				return (ft_destroy_all(philo));
			}
			ft_get_time(&(*philo)[i].time_left, (*philo)[i].current_time);
			if ((*philo)[i].died
				|| (*philo)[i].time_left > (*philo)[i].param.t_die)
			{
				ft_print_message(&(*philo)[i], 5);
				return (ft_destroy_all(philo));
			}
			pthread_mutex_unlock((*philo)[i].alive_ptr);
		}
	}
	return (0);
}

void	ft_usleep(int to_sleep)
{
	int	temp;
	int	temp_start;

	ft_get_time(&temp_start, 0);
	while (ft_get_time(&temp, temp_start) < to_sleep)
		;
}

void	*ft_life_routine(void *x)
{
	t_philo	*philo;

	philo = x;
	ft_life_routine_ext_00(philo);
	while (1)
	{
		ft_life_routine_ext_01(philo);
		if (ft_life_routine_ext_02(philo))
			break ;
		ft_life_routine_ext_03(philo);
		if (ft_life_routine_ext_04(philo))
			break ;
		ft_life_routine_ext_05(philo);
	}
	return (NULL);
}
