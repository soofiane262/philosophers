/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 20:31:53 by sel-mars          #+#    #+#             */
/*   Updated: 2022/01/31 20:31:56 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_param
{
	long	start_time;
	int		nb_philo;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		nb_eat;
	int		in_routine;
	int		nb_full_eat;
	sem_t	*sem;
}	t_param;
typedef struct s_philo
{
	int				id;
	long			elapsed_time;
	long			print_time;
	long			current_time;
	long			temp_time;
	int				nb_eat;
	int				waiting_for_fork;
	t_param			*param;

}	t_philo;
int		ft_philo_bonus(int ac, char **av);
int		ft_cop(t_philo **philo);
void	ft_putchar(char c);
int		ft_puterror_ret_1(char *str);
void	ft_putstr(char *str);
void	ft_putnbr(long nb);
long	ft_get_time(long *time, long start);
void	ft_usleep(int to_sleep, long start);
int		ft_isnum_philo(char *str);
int		ft_atoi_philo(char *str);
int		ft_parse(int ac, char **av, t_param **param);
int		ft_parse_error(t_param **param, char *str);
int		ft_print_message(t_philo *philo, int action);
#endif
