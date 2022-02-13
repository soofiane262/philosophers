/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_03_threads.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:52:05 by sel-mars          #+#    #+#             */
/*   Updated: 2022/02/02 18:52:07 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_into_threads_error(t_philo **philo, int i)
{
	pthread_mutex_destroy(&(*philo)[0].alive);
	pthread_mutex_destroy(&(*philo)[0].print);
	while (i)
		pthread_mutex_destroy(&(*philo)[i--].fork_r);
	free(*philo);
	return (1);
}

int	ft_into_threads(t_param param, t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < param.nb_philo)
	{
		if (pthread_create(&(*philo)[i].philo_id, 0, ft_life_routine,
			(void *)&(*philo)[i]))
			return (ft_into_threads_error(philo, i));
	}
	i = -1;
	while (++i < param.nb_philo)
	{
		if (pthread_detach((*philo)[i].philo_id))
			return (ft_into_threads_error(philo, i));
	}
	ft_cop(philo);
	return (0);
}

void	ft_print_message(t_philo *philo, int action)
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
		return ;
	}
	pthread_mutex_unlock(philo->print_ptr);
}

void	ft_life_routine_ext(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork_r));
	ft_print_message(philo, 1);
	pthread_mutex_lock(philo->fork_l);
	ft_print_message(philo, 1);
	ft_print_message(philo, 2);
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

void	*ft_life_routine(void *x)
{
	t_philo	*philo;

	philo = x;
	pthread_mutex_lock(philo->print_ptr);
	*(philo->in_routine_ptr) += 1;
	pthread_mutex_unlock(philo->print_ptr);
	while (1)
		if (*(philo->in_routine_ptr) == philo->param.nb_philo)
			break ;
	ft_get_time(philo->start_time_ptr, 0);
	ft_get_time(&(philo->current_time), 0);
	philo->elapsed_time = 0;
	if (!(philo->id % 2))
		ft_usleep(1, ft_get_time(&philo->temp_time, 0));
	while (1)
		ft_life_routine_ext(philo);
	return (NULL);
}
