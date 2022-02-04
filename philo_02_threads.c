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
		while (i < (*philo)[i].param.nb_philo)
		{
			// pthread_mutex_lock((*philo)[i]->alive_ptr);
			// if ((*philo)[i]->time_left > (*philo)[i]->param.t_die)
			// 	(*philo)[i]->died = 1;
			// pthread_mutex_unlock((*philo)[i]->alive_ptr);
			if ((*philo)[i].died || (*philo)[i].nb_eat == (*philo)[i].param.nb_eat)
			{
				if ((*philo)[i].died)
					ft_print_message(&(*philo)[i], 5);
				return (ft_destroy_all(philo));
			}
			i++;
		}
	}
	return (0);
}

int	ft_print_message(t_philo *philo, int action)
{
	pthread_mutex_lock(philo->print_ptr);
	if (ft_get_time(&(philo->param.elapsed_time), philo->param.start_time))
		return (0);
	ft_putnbr(philo->param.elapsed_time / 1000);
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

void	*ft_life_routine(void *x)
{
	t_philo	*philo;

	philo = x;
	if (ft_get_time(&(philo->param.current_time), 0))
		return (NULL);
	philo->time_left = 0;
	if (philo->id % 2)
	{
		philo->time_left = philo->param.t_die / 2;
		if (philo->time_left > philo->param.t_die)
		{
			ft_print_message(philo, 5);
			return (NULL);
		}
		usleep(philo->time_left);
	}
	while (1)
	{
		while (philo->time_left < philo->param.t_die && pthread_mutex_lock(&(philo->fork_r)))
			if (ft_get_time(&(philo->time_left), philo->param.current_time))
				return (NULL);
		pthread_mutex_lock(philo->alive_ptr);
		if (philo->time_left > philo->param.t_die)
			philo->died = 1;
		ft_print_message(philo, 1);
		pthread_mutex_unlock(philo->alive_ptr);
		while (philo->time_left < philo->param.t_die && pthread_mutex_lock(philo->fork_l))
			if (ft_get_time(&(philo->time_left), philo->param.current_time))
				return (NULL);
		pthread_mutex_lock(philo->alive_ptr);
		if (philo->time_left > philo->param.t_die)
			philo->died = 1;
		pthread_mutex_unlock(philo->alive_ptr);
		ft_print_message(philo, 1);
		ft_print_message(philo, 2);
		if (ft_get_time(&(philo->param.start_time), 0))
				return (NULL);
		philo->time_left = philo->param.t_eat;
		if (philo->time_left > philo->param.t_die)
			philo->time_left = philo->param.t_die + 1000;
		usleep(philo->time_left);
		pthread_mutex_lock(philo->alive_ptr);
		if (philo->time_left > philo->param.t_die)
			philo->died = 1;
		pthread_mutex_unlock(philo->alive_ptr);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(&(philo->fork_r));
		philo->nb_eat++;
		pthread_mutex_lock(philo->alive_ptr);
		pthread_mutex_unlock(philo->alive_ptr);
		ft_print_message(philo, 3);
		philo->time_left += philo->param.t_sleep;
		if (philo->time_left > philo->param.t_die && philo->param.t_die - philo->param.t_eat >= 0)
			usleep(philo->param.t_die - philo->param.t_eat + 1);
		else if (philo->time_left > philo->param.t_die && philo->param.t_die - philo->param.t_eat < 0)
			usleep(1000);
		else
			usleep(philo->param.t_sleep);
		pthread_mutex_lock(philo->alive_ptr);
		if (philo->time_left > philo->param.t_die)
			philo->died = 1;
		pthread_mutex_unlock(philo->alive_ptr);
		ft_print_message(philo, 4);
	}
	// if (ft_get_time(&(philo->param.elapsed_time), philo->param.start_time))
	// 		return (NULL);
	// if (philo->time_left > philo->param.t_die)
	// 	ft_print_message(philo, 5);
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
		(*philo)[i].print_ptr = &((*philo)[0].print);
		i++;
	}
	return (0);
}
