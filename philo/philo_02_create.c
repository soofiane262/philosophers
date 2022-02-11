/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_02_threads.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:52:05 by sel-mars          #+#    #+#             */
/*   Updated: 2022/02/02 18:52:07 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_create_philos(t_param param)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * param.nb_philo);
	if (!philo)
		return (0);
	return (philo);
}

int	ft_create_threads_ext_00(t_philo **philo)
{
	if (pthread_mutex_init(&(*philo)[0].alive, 0))
	{
		free(*philo);
		return (1);
	}
	if (pthread_mutex_init(&(*philo)[0].print, 0))
	{
		pthread_mutex_destroy(&(*philo)[0].print);
		free(*philo);
		return (1);
	}
	return (0);
}

int	ft_create_threads_ext_01(t_philo **philo, int i)
{
	if (pthread_mutex_init(&((*philo)[i].fork_r), 0))
	{
		pthread_mutex_destroy(&(*philo)[0].alive);
		pthread_mutex_destroy(&(*philo)[0].print);
		while (i)
			pthread_mutex_destroy(&(*philo)[i--].fork_r);
		free(*philo);
		return (1);
	}
	return (0);
}

int	ft_create_threads_ext_02(t_param param, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < param.nb_philo)
	{
		(*philo)[i].fork_l = &((*philo)[(i + 1) % param.nb_philo].fork_r);
		i++;
	}
	i = 0;
	while (i < param.nb_philo)
	{
		(*philo)[i].alive_ptr = &((*philo)[0].alive);
		(*philo)[i].print_ptr = &((*philo)[0].print);
		i++;
	}
	return (0);
}

int	ft_create_threads(t_param param, t_philo **philo)
{
	int	i;

	if (ft_create_threads_ext_00(philo))
		return (1);
	(*philo)[0].start_time = 0;
	(*philo)[0].in_routine = 0;
	(*philo)[0].nb_full_eat = 0;
	i = 0;
	while (i < param.nb_philo)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].nb_eat = 0;
		(*philo)[i].current_time = 0;
		(*philo)[i].start_time_ptr = &(*philo)[0].start_time;
		(*philo)[i].in_routine_ptr = &(*philo)[0].in_routine;
		(*philo)[i].nb_full_eat_ptr = &(*philo)[0].nb_full_eat;
		(*philo)[i].param = param;
		if (ft_create_threads_ext_01(philo, i))
			return (1);
		i++;
	}
	ft_create_threads_ext_02(param, philo);
	return (0);
}
