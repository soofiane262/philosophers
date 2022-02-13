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

int	ft_end(t_philo **philo, int i)
{
	kill((*philo)[0].common.eat_cop_pid, SIGINT);
	while (--i >= 0)
		kill((*philo)[i].pid, SIGINT);
	free((*philo)->param);
	free(*philo);
	sem_close((*philo)[0].param->into_fork);
	sem_close((*philo)[0].param->print);
	sem_close((*philo)[0].param->alive);
	sem_close((*philo)[0].param->nb_eat);
	sem_close((*philo)[0].param->forks);
	return (1);
}

int	ft_create_philos_ext(t_param **param, t_philo **philo, t_common *common)
{
	sem_unlink("/into_fork");
	sem_unlink("/print");
	sem_unlink("/nb_eat");
	sem_unlink("/alive");
	sem_unlink("/forks");
	(*param)->into_fork = sem_open("/into_fork", O_CREAT, 777, 0);
	(*param)->print = sem_open("/print", O_CREAT, 777, 1);
	(*param)->nb_eat = sem_open("/nb_eat", O_CREAT, 777, 0);
	(*param)->alive = sem_open("/alive", O_CREAT, 777, 1);
	(*param)->forks = sem_open("/forks", O_CREAT, 777, common->nb_philo);
	if ((*param)->print == SEM_FAILED || (*param)->alive == SEM_FAILED
		|| (*param)->forks == SEM_FAILED)
	{
		free(*param);
		free(*philo);
		return (1);
	}
	return (0);
}

t_philo	*ft_create_philos(t_common *common)
{
	int		i;
	t_param	*param;
	t_philo	*philo;

	param = (t_param *)malloc(sizeof(t_param));
	if (!param)
		return (NULL);
	philo = (t_philo *)malloc(sizeof(t_philo) * common->nb_philo);
	if (!philo)
	{
		free(param);
		return (NULL);
	}
	if (ft_create_philos_ext(&param, &philo, common))
		return (NULL);
	i = 0;
	while (i < common->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].nb_eat = 0;
		philo[i].common = *common;
		philo[i].param = param;
		i++;
	}
	return (philo);
}

int	ft_create_eat_cop_process(t_philo **philo)
{
	if ((*philo)[0].common.nb_eat > 0)
	{
		puts("check");
		(*philo)[0].common.eat_cop_pid = fork();
		if ((*philo)[0].common.eat_cop_pid == -1)
		{
			ft_end(philo, (*philo)[0].common.nb_philo);
			return (1);
		}
		if ((*philo)[0].common.eat_cop_pid == 0)
			ft_eat_cop(philo);
	}
	return (1);
}

int	ft_create_philo_processes(t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < (*philo)[0].common.nb_philo)
	{
		(*philo)[i].pid = fork();
		if ((*philo)[i].pid == -1)
			return (ft_end(philo, i));
		if ((*philo)[i].pid == 0)
			ft_life_routine(&(*philo)[i]);
	}
	i = -1;
	while (++i < (*philo)[0].common.nb_philo)
		sem_post((*philo)[0].param->into_fork);
	if ((*philo)[0].common.nb_eat > 0)
	{
		puts("check");
		(*philo)[0].common.eat_cop_pid = fork();
		if ((*philo)[0].common.eat_cop_pid == -1)
			return (ft_end(philo, (*philo)[0].common.nb_philo));
		if ((*philo)[0].common.eat_cop_pid == 0)
			ft_eat_cop(philo);
	}
	return (0);
}
