/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_04_routine_ext_0.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:52:05 by sel-mars          #+#    #+#             */
/*   Updated: 2022/02/02 18:52:07 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_life_routine_ext_00(t_philo *philo)
{
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
		while (*(philo->in_routine_ptr) != philo->param.nb_philo)
			;
		pthread_mutex_unlock(philo->alive_ptr);
	}
	else
	{
		pthread_mutex_lock(philo->alive_ptr);
		pthread_mutex_unlock(philo->alive_ptr);
	}
	ft_get_time(&philo->time_in_print, 0);
	ft_get_time(&(philo->current_time), 0);
	philo->time_left = 0;
	philo->print_time = 0;
	if (!(philo->id % 2))
		ft_usleep(philo->param.t_die / 2);
}

void	ft_life_routine_ext_01(t_philo *philo)
{
	philo->waiting_for_fork = 2;
	pthread_mutex_lock(&(philo->fork_r));
	ft_print_message(philo, 1);
	philo->waiting_for_fork = 1;
	pthread_mutex_lock(philo->fork_l);
	ft_print_message(philo, 1);
	philo->waiting_for_fork = 0;
	ft_print_message(philo, 2);
	ft_get_time(&(philo->current_time), 0);
}

int	ft_life_routine_ext_02(t_philo *philo)
{
	if (philo->param.t_eat > philo->param.t_die)
	{
		philo->print_time += philo->param.t_die + 1;
		ft_usleep(philo->param.t_die + 1);
		*(philo->died_ptr) = philo->id;
		return (1);
	}
	return (0);
}

void	ft_life_routine_ext_03(t_philo *philo)
{
	ft_usleep(philo->param.t_eat);
	philo->nb_eat++;
	if (philo->nb_eat == philo->param.nb_eat)
		*(philo->nb_full_eat_ptr) += 1;
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(&(philo->fork_r));
	philo->print_time += philo->param.t_eat;
	ft_print_message(philo, 3);
}

int	ft_life_routine_ext_04(t_philo *philo)
{
	if (philo->param.t_sleep + philo->param.t_eat > philo->param.t_die)
	{
		if (philo->param.t_die - philo->param.t_eat > 0)
		{
			philo->print_time += philo->param.t_die - philo->param.t_eat + 1;
			ft_usleep(philo->param.t_die - philo->param.t_eat + 1);
		}
		else
		{
			philo->print_time += 1;
			ft_usleep(1);
		}
		*(philo->died_ptr) = philo->id;
		return (1);
	}
	return (0);
}
