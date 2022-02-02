/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_01_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 20:45:55 by sel-mars          #+#    #+#             */
/*   Updated: 2022/01/31 20:45:56 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isnum_philo(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (!str[i])
		return (0);
	else
		return (-1);
}

int	ft_atoi_philo(char *str)
{
	int	i;
	int	ret;

	if (!str || ft_isnum_philo(str) == -1)
		return (-1);
	i = 0;
	ret = 0;
	while (str[i])
	{
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	return (ret);
}

int	ft_parse(int ac, char **av, t_param *param)
{
	if (ac != 5 && ac != 6)
	{
		ft_putstr("Error\nInvalid number of arguments\n");
		return (1);
	}
	param->nb_philo = ft_atoi_philo(av[1]);
	param->t_die = 1000 * ft_atoi_philo(av[2]);
	param->t_eat = 1000 * ft_atoi_philo(av[3]);
	param->t_sleep = 1000 * ft_atoi_philo(av[4]);
	// ft_putnbr(1000);
	if (ac == 6)
		param->nb_eat = ft_atoi_philo(av[5]);
	else
		param->nb_eat = -2;
	if (param->nb_philo == -1 || param->t_die == -1 || param->t_eat == -1
		|| param->t_sleep == -1 || param->nb_eat == -1)
	{
		ft_putstr("Error\nInvalid argument\n");
		return (1);
	}
	return (0);
}
