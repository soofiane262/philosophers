/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_02_threads_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:52:05 by sel-mars          #+#    #+#             */
/*   Updated: 2022/02/02 18:52:07 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_eat_cop(t_philo **philo)
{
	int	count;

	count = 0;
	while (1)
	{
		sem_wait((*philo)[0].param->nb_eat);
		count++;
		if (count == (*philo)[0].common.nb_philo)
		{
			sem_wait((*philo)[0].param->print);
			exit(0);
		}
	}
}

void	*ft_die_cop(void *x)
{
	t_philo	*philo;

	philo = x;
	while (1)
	{
		sem_wait(philo->param->alive);
		ft_get_time(&philo->elapsed_time, philo->current_time);
		if (philo->elapsed_time > philo->common.t_die)
		{
			ft_print_message(philo, 5);
			exit(0);
		}
		sem_post(philo->param->alive);
	}
}

void	ft_print_message(t_philo *philo, int action)
{
	sem_wait(philo->param->print);
	ft_get_time(&(philo->print_time), philo->common.start_time);
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
	sem_post(philo->param->print);
}

void	ft_life_routine_ext(t_philo *philo)
{
	sem_wait(philo->param->forks);
	ft_print_message(philo, 1);
	sem_wait(philo->param->forks);
	ft_print_message(philo, 1);
	ft_print_message(philo, 2);
	ft_get_time(&philo->current_time, 0);
	ft_usleep(philo->common.t_eat, ft_get_time(&philo->temp_time, 0));
	philo->nb_eat++;
	if (philo->nb_eat == philo->common.nb_eat)
		sem_post(philo->param->nb_eat);
	sem_post(philo->param->forks);
	sem_post(philo->param->forks);
	ft_print_message(philo, 3);
	ft_usleep(philo->common.t_sleep, ft_get_time(&philo->temp_time, 0));
	ft_print_message(philo, 4);
}

void	ft_life_routine(t_philo *philo)
{
	sem_wait(philo->param->into_fork);
	pthread_create(&philo->cop_thread, 0, &ft_die_cop, (void *)philo);
	ft_get_time(&philo->common.start_time, 0);
	ft_get_time(&(philo->current_time), 0);
	philo->elapsed_time = 0;
	if (!(philo->id % 2))
		ft_usleep(philo->common.t_eat / 2, ft_get_time(&philo->temp_time, 0));
	while (1)
		ft_life_routine_ext(philo);
}
