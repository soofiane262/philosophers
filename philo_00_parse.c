/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_00_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 20:45:55 by sel-mars          #+#    #+#             */
/*   Updated: 2022/01/31 20:45:56 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_itoa_philo(char *str)
{
	int	ret;


}

int	ft_parse(int ac, char **av, t_param param)
{
	(void)av;
	(void)param;
	if (ac != 5 && ac != 6)
	{
		ft_putstr("Error\nInvalid number of arguments\n");
		return (1);
	}

	return (0);
}
