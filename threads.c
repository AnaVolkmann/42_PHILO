/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:56:10 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/10/24 17:23:38 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Checks if the philosopher is marked as dead.
 *
 * This function checks the state of the dead flag for the philosopher,
 * indicating whether they have died.
 *
 * @param philo Pointer to the philosopher structure.
 * @return 1 if the philosopher is dead, 0 otherwise.
 */
int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

/**
 * @brief Philosopher thread routine.
 *
 * This function represents the routine of a philosopher, including
 * sleeping, eating, and thinking. It also accounts for synchronization
 * based on the dead flag.
 *
 * @param pointer Pointer to the philosopher structure.
 * @return Pointer to the philosopher structure.
 */
void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (pointer);
}

/**
 * @brief Creates and manages philosopher threads.
 *
 * This function initializes philosopher threads and an observer thread.
 * It also handles any errors that occur during thread creation and joining.
 *
 * @param program Pointer to the program structure containing philosopher data.
 * @param forks Array of mutexes for managing forks.
 * @return 0 on success.
 */
int	thread_create(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	i = 0;
	while (i < program->philos[0].num_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_routine,
				&program->philos[i]) != 0)
			destroy_all("Thread creation error", program, forks);
		i++;
	}
	if (pthread_create(&observer, NULL, &monitor, program->philos) != 0)
		destroy_all("Thread creation error", program, forks);
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		destroy_all("Thread join error", program, forks);
	while (i < program->philos[0].num_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destroy_all("Thread join error", program, forks);
		i++;
	}
	return (0);
}
