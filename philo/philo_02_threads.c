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
		pthread_mutex_destroy(&((*philo)[i].fork_r));
	pthread_mutex_destroy((*philo)[0].alive_ptr);
	pthread_mutex_destroy((*philo)[0].print_ptr);
	return (0);
}

int	ft_into_threads(t_param param, t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < param.nb_philo)
		if (pthread_create(&(*philo)[i].philo_id, 0, ft_life_routine, (void *)&(*philo)[i]))
			return (1);
	i = -1;
	while (++i < param.nb_philo)
		if (pthread_detach((*philo)[i].philo_id))
			return (1);
	ft_cop(philo);
	return (0);
}

int	ft_cop(t_philo **philo)
{
	int			i;

	while (1)
	{
		i = 0;
		while (i < (*philo)[i].param.nb_philo && (*philo)[0].in_routine == (*philo)[i].param.nb_philo
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
			pthread_mutex_unlock((*philo)[i].alive_ptr);
			i++;
		}
	}
	return (0);
}

int	ft_print_message(t_philo *philo, int action)
{
	pthread_mutex_lock(philo->print_ptr);
	ft_get_time(&(philo->print_time), *(philo->start_time_ptr));
	ft_putnbr(philo->print_time);
	ft_putstr("	");
	ft_putnbr(philo->id);
	if (action == 1)
		ft_putstr("	has taken a fork\n");
	else if (action == 2)
		ft_putstr("	is eating\n");
	else if (action == 3)
		ft_putstr("	is sleeping\n");
	else if (action == 4)
		ft_putstr("	is thinking\n");
	else if (action == 5)
	{
		ft_putstr("	died\n");
		return (0);
	}
	pthread_mutex_unlock(philo->print_ptr);
	return (1);
}

void	ft_usleep(int to_sleep, long start)
{
	long	temp;

	while (ft_get_time(&temp, 0) < start + to_sleep)
		usleep(50);
}

void	*ft_life_routine(void *x)
{
	t_philo	*philo;

	philo = x;
	pthread_mutex_lock(philo->print_ptr);
	*(philo->in_routine_ptr) += 1;
	pthread_mutex_unlock(philo->print_ptr);
	while (1)
		if (*(philo->in_routine_ptr) == philo->param.nb_philo)
			break;
	ft_get_time(philo->start_time_ptr, 0);
	ft_get_time(&(philo->current_time), 0);
	philo->elapsed_time = 0;
	if (!(philo->id % 2))
		ft_usleep(1, ft_get_time(&philo->temp_time, 0));
	while (1)
	{
		philo->waiting_for_fork = 1;
		pthread_mutex_lock(&(philo->fork_r));
		ft_print_message(philo, 1);
		pthread_mutex_lock(philo->fork_l);
		ft_print_message(philo, 1);
		ft_print_message(philo, 2);
		philo->waiting_for_fork = 0;
		ft_get_time(&(philo->current_time), 0);
		ft_usleep(philo->param.t_eat, ft_get_time(&philo->temp_time, 0));
		philo->nb_eat++;
		if (philo->nb_eat == philo->param.nb_eat)
			*(philo->nb_full_eat_ptr) += 1;
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(&(philo->fork_r));
		ft_print_message(philo, 3);
		ft_usleep(philo->param.t_sleep, ft_get_time(&philo->temp_time, 0));
		ft_print_message(philo, 4);
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
	if (pthread_mutex_init(&(*philo)[0].print, 0))
	{
		pthread_mutex_destroy(&(*philo)[0].print);
		free(*philo);
		return (1);
	}
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
		if (pthread_mutex_init(&((*philo)[i].fork_r), 0))
		{
			pthread_mutex_destroy(&(*philo)[0].alive);
			pthread_mutex_destroy(&(*philo)[0].print);
			while (i)
				pthread_mutex_destroy(&(*philo)[i--].fork_r);
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
		(*philo)[i].print_ptr = &((*philo)[0].print);
		i++;
	}
	return (0);
}
