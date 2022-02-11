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
	long	start_time;
	int		nb_philo;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		nb_eat;
}	t_param;
typedef struct s_philo
{
	int				id;
	long			elapsed_time;
	long			print_time;
	long			current_time;
	long			temp_time;
	int				nb_eat;
	int				first_in;
	int				waiting_for_fork;
	long			start_time;
	long			*start_time_ptr;
	int				nb_full_eat;
	int				*nb_full_eat_ptr;
	int				in_routine;
	int				*in_routine_ptr;
	t_param			param;
	pthread_t		philo_id;
	pthread_mutex_t	fork_r;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	alive;
	pthread_mutex_t	*alive_ptr;
	pthread_mutex_t	print;
	pthread_mutex_t	*print_ptr;

}	t_philo;
int		ft_philo(int ac, char **av);
int		ft_cop(t_philo **philo);
void	ft_putchar(char c);
int		ft_puterror_ret_1(char *str);
void	ft_putstr(char *str);
void	ft_putnbr(long nb);
long	ft_get_time(long *time, long start);
void	ft_usleep(int to_sleep, long start);
int		ft_destroy_all(t_philo **philo);
int		ft_isnum_philo(char *str);
int		ft_atoi_philo(char *str);
int		ft_parse(int ac, char **av, t_param *param);
t_philo	*ft_create_philos(t_param param);
int		ft_create_threads_ext_00(t_philo **philo);
int		ft_create_threads_ext_01(t_philo **philo, int i);
int		ft_create_threads_ext_02(t_param param, t_philo **philo);
int		ft_create_threads(t_param param, t_philo **philo);
int		ft_into_threads_error(t_philo **philo, int i);
int		ft_into_threads(t_param param, t_philo **philo);
int		ft_print_message(t_philo *philo, int action);
void	ft_life_routine_ext(t_philo *philo);
void	*ft_life_routine(void *x);
#endif
