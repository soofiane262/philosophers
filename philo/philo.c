/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 20:31:49 by sel-mars          #+#    #+#             */
/*   Updated: 2022/01/31 20:31:49 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo(int ac, char **av)
{
	t_param	param;
	t_philo	*philo;

	ft_get_time(&(param.start_time), 0);
	if (ft_parse(ac, av, &param))
		return (1);
	philo = ft_create_philos(param);
	if (!philo || ft_create_threads(param, &philo))
		return (ft_puterror_ret_1("Error creating philosophers\n"));
	if (ft_into_threads(param, &philo))
		return (ft_puterror_ret_1("Error dealing with threads\n"));
	return (0);
}
