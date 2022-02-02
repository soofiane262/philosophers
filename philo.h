/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 20:31:53 by sel-mars          #+#    #+#             */
/*   Updated: 2022/01/31 20:31:56 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_param
{
	int	start_time;
	int	current_time;
	int	elapsed_time;
	int	nb_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	nb_eat;
}	t_param;
typedef struct s_philo
{
	int				id;
	int				time_left;
	int				nb_eat;
	int				died;
	t_param			param;
	pthread_mutex_t	fork_r;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	alive;
	pthread_mutex_t	*alive_ptr;
	pthread_t		philo_id;

}	t_philo;
int		ft_philo(int ac, char **av);
int		ft_parse(int ac, char **av, t_param *param);
t_philo	*ft_create_philos(t_param param);
int		ft_create_threads(t_param param, t_philo **philo);
int		ft_into_threads(t_param param, t_philo **philo);
void	*ft_life_routine(void *x);
int		ft_get_time(int *time, int start);
void	ft_putchar(char c);
void	ft_putstr(char *str);
int		ft_puterror_ret_1(char *str);
void	ft_putnbr(int nb);
int		ft_atoi_philo(char *str);
int		ft_isnum_philo(char *str);
#endif
