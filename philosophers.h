/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:17:47 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/10/14 16:46:41 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

# define PHILO_MAX 300

typedef struct	s_philo
{
	pthread_t	thread;
	int				id;	// id of the process running
	int				eating;
	int				meals_eaten; // counter for the last param
	int		last_meal;
	size_t	t_die;	// time to die
	size_t	t_eat;	//	 time to eat
	size_t	t_sleep;	// time to sleep
	size_t	start_time;	// counter
	long int	num_philos;	// number of philos
	int			x_to_eat;	// time to eat before dieing
	int			*dead;			// dead flag
	pthread_mutex_t		*r_fork;	//lock for right fork
	pthread_mutex_t		*l_fork;	//lock for lesft fork
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*meal_lock;
}				t_philo;

typedef struct s_program
{
	int					dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;


/***********************UTILS*******************/

int ft_atoi(char *str);
int ft_strlen(char *str);

/***********************HANDLE_ARGS**************/

int	valid_args(char **argv);
int	check_args(char *argv);

/***********************INIT*********************/

void	init_input(t_philo *philo, char **argv);
void	init_program(t_program *program, t_philo *philos);
void	init_forks(pthread_mutex_t *forks, int philo_num);
void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks, char **argv);

#endif