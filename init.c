/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:05:40 by druina            #+#    #+#             */
/*   Updated: 2024/10/25 16:45:24 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Initializes the input parameters for the philosopher.
 *
 * This function sets the timing parameters and number of philosophers
 * based on user input from command-line arguments.
 *
 * @param philo Pointer to the philosopher structure to initialize.
 * @param argv Array of command-line arguments.
 */
void	init_input(t_philo *philo, char **argv)
{
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->num_of_philos = ft_atoi(argv[1]);
	if (argv[5])
		philo->x_times_to_eat = ft_atoi(argv[5]);
	else
		philo->x_times_to_eat = -1;
}

/**
 * @brief Initializes the philosophers and their attributes.
 *
 * This function assigns unique IDs, initializes their states, and sets
 * up their mutex locks and fork pointers.
 *
 * @param philos Array of philosopher structures to initialize.
 * @param program Pointer to the program structure.
 * @param forks Array of mutexes for the forks.
 * @param argv Array of command-line arguments.
 */
void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks,
		char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		init_input(&philos[i], argv);
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead = &program->dead_flag;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].num_of_philos - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}

/**
 * @brief Initializes the mutexes for the forks.
 *
 * This function creates mutexes for each fork to control access
 * during dining.
 *
 * @param forks Array of mutexes to initialize.
 * @param philo_num Number of philosophers (forks).
 */
void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

/**
 * @brief Initializes the program structure.
 *
 * This function sets the initial state of the program and initializes
 * the mutexes for synchronization.
 *
 * @param program Pointer to the program structure to initialize.
 * @param philos Pointer to the array of philosophers.
 */
void	init_program(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}
