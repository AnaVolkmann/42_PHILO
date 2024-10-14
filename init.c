/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:16:02 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/10/14 17:55:06 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/** @brief Initializes the input parameters for a philosopher.
 * 
 * @param philo Pointer to a philosopher structure to be initialized.
 * @param argv Command-line arguments containing timing and count information.*/
void	init_input(t_philo *philo, char **argv)
{
	philo->t_die = ft_atoi(argv[2]);
	philo->t_eat = ft_atoi(argv[3]);
	philo->t_sleep = ft_atoi(argv[4]);
	philo->num_philos = ft_atoi(argv[1]);
	if (argv[5])
		philo->x_to_eat = ft_atoi(argv[5]);
	else
		philo->x_to_eat = -1;
}

/** @brief Initializes the program structure and its associated mutexes.
 * 
 * @param program Pointer to the program structure to be initialized.
 * @param philos Pointer to the philosophers array.*/
void	init_program(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}

/** @brief Initializes the mutexes for forks used by philosophers.
 * 
 * @param forks Array of mutexes for forks.
 * @param philo_num Number of philosophers (and thus forks).*/
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

/** @brief Initializes each philosopher's attributes and assigns their forks.
 * 
 * @param philos Pointer to the array of philosophers to be initialized.
 * @param program Pointer to the program structure.
 * @param forks Array of mutexes for forks.
 * @param argv Command-line arguments to extract necessary data..*/
void	init_philos(t_philo *philos, t_program *program,
				pthread_mutex_t *forks, char **argv)
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
			philos[i].r_fork = &forks[philos[i].num_philos - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}
