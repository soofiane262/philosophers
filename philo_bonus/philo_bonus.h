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
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>

typedef struct s_common
{
	pid_t	eat_cop_pid;
	long	start_time;
	int		nb_philo;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		nb_eat;
	int		in_routine;
}	t_common;
typedef struct s_param
{
	sem_t	*into_fork;
	sem_t	*print;
	sem_t	*alive;
	sem_t	*nb_eat;
	sem_t	*forks;
}	t_param;
typedef struct s_philo
{
	int				id;
	pid_t			pid;
	long			elapsed_time;
	long			print_time;
	long			current_time;
	long			temp_time;
	int				nb_eat;
	pthread_t		cop_thread;
	t_common		common;
	t_param			*param;

}	t_philo;
int		ft_philo_bonus(int ac, char **av);
void	ft_putchar(char c);
int		ft_puterror_ret_1(char *str);
void	ft_putstr(char *str);
void	ft_putnbr(long nb);
long	ft_get_time(long *time, long start);
void	ft_usleep(int to_sleep, long start);
int		ft_isnum_philo(char *str);
int		ft_atoi_philo(char *str);
int		ft_parse(int ac, char **av, t_common *common);
t_philo	*ft_create_philos(t_common *common);
int		ft_create_philo_processes(t_philo **philo);
void	ft_life_routine(t_philo *philo);
void	*ft_die_cop(void *x);
void	ft_eat_cop(t_philo **philo);
void	ft_life_routine_ext(t_philo *philo);
void	ft_check(t_philo **philo);
int		ft_end(t_philo **philo, int i);
void	ft_print_message(t_philo *philo, int action);
#endif
