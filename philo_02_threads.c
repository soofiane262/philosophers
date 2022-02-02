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

int	ft_destroy_all(t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < (*philo)[0].param.nb_philo)
	{
		pthread_detach((*philo)[i].philo_id);
		pthread_mutex_destroy(&((*philo)[i].fork_r));
	}
	// pthread_mutex_unlock((*philo)[0].alive_ptr);
	pthread_mutex_destroy((*philo)[0].alive_ptr);
	return (0);
}

int	ft_into_threads(t_param param, t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < param.nb_philo)
		if (pthread_create(&(*philo)[i].philo_id, 0, &ft_life_routine, &(*philo)[i]))
			return (1);
	while (1)
	{
		i = -1;
		while (++i < param.nb_philo)
		{
			if ((*philo)[i].died)
				return (ft_destroy_all(philo));
		}
	}
	return (0);
}

void	*ft_life_routine(void *x)
{
	t_philo	*philo;

	philo = x;
	if (!(philo->id % 2))
		usleep(10000);
	if (ft_get_time(&(philo->param.current_time), 0))
		return (NULL);
	philo->time_left = 0;




	while (1)
	{
		while (philo->time_left < philo->param.t_die && pthread_mutex_lock(&(philo->fork_r)))
			if (ft_get_time(&(philo->time_left), philo->param.current_time))
				return (NULL);
		pthread_mutex_lock(philo->alive_ptr);
		if (philo->time_left >= philo->param.t_die)
			break ;
		pthread_mutex_unlock(philo->alive_ptr);
		if (ft_get_time(&(philo->param.elapsed_time), philo->param.start_time))
			return (NULL);
		printf("%d	%d	has taken a fork\n", philo->param.elapsed_time / 1000, philo->id);
		while (philo->time_left < philo->param.t_die && pthread_mutex_lock(philo->fork_l))
			if (ft_get_time(&(philo->time_left), philo->param.current_time))
				return (NULL);
		pthread_mutex_lock(philo->alive_ptr);
		if (philo->time_left >= philo->param.t_die)
			break ;
		pthread_mutex_unlock(philo->alive_ptr);
		if (ft_get_time(&(philo->param.elapsed_time), philo->param.start_time))
			return (NULL);
		printf("%d	%d	has taken a fork\n", philo->param.elapsed_time / 1000, philo->id);
		if (ft_get_time(&(philo->param.elapsed_time), philo->param.start_time))
			return (NULL);
		printf("%d	%d	is eating\n", philo->param.elapsed_time / 1000, philo->id);
		usleep(philo->param.t_eat);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(&(philo->fork_r));
		pthread_mutex_lock(philo->alive_ptr);
		pthread_mutex_unlock(philo->alive_ptr);
		if (ft_get_time(&(philo->param.elapsed_time), philo->param.start_time))
			return (NULL);
		printf("%d	%d	is sleeping\n", philo->param.elapsed_time / 1000, philo->id);
		usleep(philo->param.t_sleep);
		philo->time_left = philo->param.t_sleep;
		pthread_mutex_lock(philo->alive_ptr);
		if (philo->time_left >= philo->param.t_die)
			break ;
		pthread_mutex_unlock(philo->alive_ptr);
		if (ft_get_time(&(philo->param.elapsed_time), philo->param.start_time))
			return (NULL);
		printf("%d	%d	is thinking\n", philo->param.elapsed_time / 1000, philo->id);
	}
	if (ft_get_time(&(philo->param.elapsed_time), philo->param.start_time))
			return (NULL);
	if (philo->time_left >= philo->param.t_die)
	{
		printf("%d	%d	died\n", philo->param.elapsed_time / 1000, philo->id);
		philo->died = 1;
	}
	return (NULL);
}

t_philo	*ft_create_philos(t_param param)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * param.nb_philo);
	if (!philo)
		return (0);
	return (philo);
}

int	ft_create_threads(t_param param, t_philo **philo)
{
	int		i;

	if (pthread_mutex_init(&(*philo)[0].alive, 0))
	{
		free(*philo);
		return (1);
	}
	i = 0;
	while (i < param.nb_philo)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].died = 0;
		(*philo)[i].nb_eat = 0;
		(*philo)[i].param = param;
		if (pthread_mutex_init(&((*philo)[i].fork_r), 0))
		{
			free(*philo);
			return (1);
		}
		i++;
	}
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
		i++;
	}
	return (0);
}
