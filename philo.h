/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:20:06 by druina            #+#    #+#             */
/*   Updated: 2024/10/25 16:48:03 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 300

typedef struct s_philo
{
	pthread_t		thread;// Thread representing the philosopher's life
	int				id;// identifier for the philosopher
	int				eating;//Flag if philo is eating (1:eating, 0:not eating)
	int				meals_eaten;//Counter for num of meals eaten by the philo
	size_t			last_meal;//Timestamp of the last meal eaten
	size_t			time_to_die;//Time limit (in milliseconds) before the philo dies
	size_t			time_to_eat;//Time (in milliseconds) taken to eat a meal
	size_t			time_to_sleep;//Time (in milliseconds) taken to sleep
	size_t			start_time;//Start time of the philosopher's activity
	int				num_of_philos;//Total number of philosophers in the simulation
	int				x_times_to_eat; //No. meals to eat before they can stop -1 unlimit
	int				*dead;//Pointer to flag if the philo is dead 1:dead,0:alive
	pthread_mutex_t	*r_fork;//Pointer to the mutex for the right fork
	pthread_mutex_t	*l_fork;//Pointer to the mutex for the left fork
	pthread_mutex_t	*write_lock;//Ptn mutex that writes output logging actions
	pthread_mutex_t	*dead_lock;//Pointer to the mutex for checking the dead flag
	pthread_mutex_t	*meal_lock;// Pointer to the mutex for tracking meals
}				t_philo;

typedef struct s_program
{
	int				dead_flag;// Flag if any philo has died 1-dead, 0-all alive
	pthread_mutex_t	dead_lock;// Mutex for synchronizing access to the dead flag
	pthread_mutex_t	meal_lock;// Mutex for synchronizing meal tracking
	pthread_mutex_t	write_lock;// Mutex for synchronizing output writing
	t_philo			*philos;// Pointer to the array of philosophers
}				t_program;

/***********************UTILS*******************/

int		ft_atoi(char *str);
int		ft_strlen(char *str);
int		ft_usleep(size_t milliseconds);
size_t	get_current_time(void);
void	destroy_all(char *str, t_program *program, pthread_mutex_t *forks);

/***********************HANDLE_ARGS**************/

int		check_valid_args(char **argv);
int		check_arg_content(char *argv);

/***********************INIT*********************/

void	init_input(t_philo *philo, char **argv);
void	init_program(t_program *program, t_philo *philos);
void	init_forks(pthread_mutex_t *forks, int philo_num);
void	init_philos(t_philo *philos, t_program *program,
			pthread_mutex_t *forks, char **argv);

/************************ACTIONS******************/

void	ft_eat(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_sleep(t_philo *philo);

/*************************THREADS*****************/

int		dead_loop(t_philo *philo);
void	*philo_routine(void *pointer);
int		thread_create(t_program *program, pthread_mutex_t *forks);

/************************MONITORING**************/

void	print_message(char *str, t_philo *philo, int id);
int		check_if_dead(t_philo *philos);
void	*monitor(void *pointer);
int		check_if_all_ate(t_philo *philo);
int		philosopher_dead(t_philo *philo, size_t time_to_die);

#endif
