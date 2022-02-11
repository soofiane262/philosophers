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
	pthread_mutex_destroy((*philo)[0].alive_ptr);
	return (0);
}

int	ft_into_threads(t_param param, t_philo **philo)
{
	int			i;
	// t_philo_ptr	philo_ptr;

	// philo_ptr.philo = philo;
	i = -1;
	while (++i < param.nb_philo)
		if (pthread_create(&(*philo)[i].philo_id, 0, ft_life_routine, (void *)&(*philo)[i]))
			return (1);
	ft_cop(philo);
	// pthread_create(&philo_ptr.cop, 0, ft_cop, (void *)&philo_ptr);
	return (0);
}

int	ft_cop(t_philo **philo)
{
	int			i;

	while (1)
	{
		i = 0;
		while (i < (*philo)[i].param.nb_philo && (*philo)[0].in_routine == (*philo)[i].param.nb_philo)
		{
			pthread_mutex_lock((*philo)[i].alive_ptr);
			if ((*philo)[0].nb_full_eat == (*philo)[i].param.nb_philo)
				return (ft_destroy_all(philo));
			// if ((*philo)[i].waiting_for_fork)
			ft_get_time(&(*philo)[i].time_left, (*philo)[i].current_time);
			if ((*philo)[i].died || (*philo)[i].time_left > (*philo)[i].param.t_die)
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
	ft_get_time(&(philo->print_time), philo->param.start_time);
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

void	ft_usleep(int to_sleep)
{
	int	temp;
	int	temp_start;

	ft_get_time(&temp_start, 0);
	while (ft_get_time(&temp, temp_start) < to_sleep);
}

void	*ft_life_routine(void *x)
{
	t_philo	*philo;

	philo = x;
	pthread_mutex_lock(philo->print_ptr);
	if (!*(philo->in_routine_ptr))
	{
		pthread_mutex_lock(philo->alive_ptr);
		philo->first_in = 1;
	}
	*(philo->in_routine_ptr) += 1;
	pthread_mutex_unlock(philo->print_ptr);
	if (philo->first_in)
	{
		while (*(philo->in_routine_ptr) != philo->param.nb_philo);
		pthread_mutex_unlock(philo->alive_ptr);
	}
	else
	{
		pthread_mutex_lock(philo->alive_ptr);
		pthread_mutex_unlock(philo->alive_ptr);
	}
	ft_get_time(&(philo->current_time), 0);
	philo->time_left = 0;
	philo->print_time = 0;
	if (!(philo->id % 2))
	{
		ft_usleep(philo->param.t_die / 2);
		philo->time_left = philo->param.t_die / 2;
	}
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
		if (philo->param.t_eat > philo->param.t_die)
		{
			ft_usleep(philo->param.t_die + 1);
			*(philo->died_ptr) = philo->id;
			break ;
		}
		ft_usleep(philo->param.t_eat);
		philo->nb_eat++;
		if (philo->nb_eat == philo->param.nb_eat)
			*(philo->nb_full_eat_ptr) += 1;
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(&(philo->fork_r));
		ft_print_message(philo, 3);
		if (philo->param.t_sleep + philo->param.t_eat > philo->param.t_die)
		{
			if (philo->param.t_die - philo->param.t_eat > 0)
				ft_usleep(philo->param.t_die - philo->param.t_eat + 1);
			else
				ft_usleep(1);
			*(philo->died_ptr) = philo->id;
			break ;
		}
		ft_get_time(&(philo->current_time), 0);
		philo->current_time += philo->param.t_eat;
		ft_usleep(philo->param.t_sleep);
		philo->nb_sleep++;
		ft_print_message(philo, 4);
		ft_get_time(&(philo->current_time), 0);
		philo->current_time += philo->param.t_eat + philo->param.t_sleep;
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
		free(*philo);
		return (1);
	}
	(*philo)[0].nb_full_eat = 0;
	(*philo)[0].in_routine = 0;
	(*philo)[0].died = 0;
	i = 0;
	while (i < param.nb_philo)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].died = 0;
		(*philo)[i].nb_eat = 0;
		(*philo)[i].nb_sleep = 0;
		(*philo)[i].died_ptr = &(*philo)[0].died;
		(*philo)[i].in_routine_ptr = &(*philo)[0].in_routine;
		(*philo)[i].nb_full_eat_ptr = &(*philo)[0].nb_full_eat;
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
		(*philo)[i].print_ptr = &((*philo)[0].print);
		i++;
	}
	return (0);
}
