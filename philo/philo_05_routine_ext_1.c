/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_05_routine_ext_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:52:05 by sel-mars          #+#    #+#             */
/*   Updated: 2022/02/02 18:52:07 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_life_routine_ext_05(t_philo *philo)
{
	ft_get_time(&(philo->current_time), 0);
	philo->current_time += philo->param.t_eat;
	ft_usleep(philo->param.t_sleep);
	philo->print_time += philo->param.t_sleep;
	ft_print_message(philo, 4);
	ft_get_time(&(philo->current_time), 0);
	philo->current_time += philo->param.t_eat + philo->param.t_sleep;
}

void	ft_print_message_ext(t_philo *philo, int action)
{
	if (!(philo->id % 2) && philo->waiting_for_fork == 2 && !philo->nb_eat)
		philo->print_time += philo->param.t_eat;
	if (!(philo->id % 2) && philo->waiting_for_fork == 1 && !philo->nb_eat
		&& philo->temp_time >= philo->param.t_eat - 10)
		philo->print_time += philo->param.t_eat;
	if (philo->id % 2 && !philo->nb_eat && philo->waiting_for_fork == 1
		&& philo->temp_time >= philo->param.t_eat - 10)
		philo->print_time += philo->param.t_eat;
	if (action == 1 && philo->waiting_for_fork == 1
		&& philo->temp_time >= philo->param.t_eat - 10 && philo->nb_eat)
		philo->print_time += philo->param.t_eat;
	else if (action == 5 && philo->waiting_for_fork)
		philo->print_time += philo->time_left;
}

int	ft_print_message(t_philo *philo, int action)
{
	pthread_mutex_lock(philo->print_ptr);
	ft_get_time(&philo->temp_time, philo->time_in_print);
	ft_print_message_ext(philo, action);
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
	ft_get_time(&philo->time_in_print, 0);
	pthread_mutex_unlock(philo->print_ptr);
	return (1);
}
