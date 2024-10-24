/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:31:06 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/10/24 17:22:22 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Prints a message with a timestamp for the philosopher.
 *
 * This function prints a message indicating the state of the philosopher,
 * including the time since the philosopher started.
 *
 * @param str Message string to print.
 * @param philo Pointer to the philosopher structure.
 * @param id The ID of the philosopher.
 */
void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!dead_loop(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

/**
 * @brief Checks if the philosopher has died.
 *
 * This function checks if the philosopher's last meal was longer than
 * the time to die and if they are not currently eating.
 *
 * @param philo Pointer to the philosopher structure.
 * @param time_to_die The time limit for the philosopher before they die.
 * @return 1 if the philosopher is dead, 0 otherwise.
 */
int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if ((get_current_time() - philo->last_meal >= time_to_die)
		&& philo->eating == 0)
	{
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

/**
 * @brief Checks if any philosopher has died.
 *
 * This function iterates through all philosophers and checks if any
 * philosopher is dead. If so, it prints the death message and updates
 * the dead flag.
 *
 * @param philos Array of philosopher structures.
 * @return 1 if any philosopher has died, 0 otherwise.
 */
int	check_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_philos)
	{
		if (philosopher_dead(&philos[i], philos[i].t_die))
		{
			print_message("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Checks if all philosophers have eaten the required number of meals.
 *
 * This function verifies if each philosopher has eaten the specified number
 * of meals, and if so, sets the dead flag to indicate completion.
 *
 * @param philos Array of philosopher structures.
 * @return 1 if all philosophers have eaten the required meals, 0 otherwise.
 */
int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos[0].x_to_eat == -1)
		return (0);
	while (i < philos[0].num_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].x_to_eat)
			finished_eating++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (finished_eating == philos[0].num_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

/**
 * @brief Monitor thread routine to check philosopher states.
 *
 * This function runs in a separate thread and continuously checks if any
 * philosopher has died or if all have eaten the required meals.
 *
 * @param pointer Pointer to the philosopher array.
 * @return Pointer to the philosopher array.
 */
void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
		if (check_if_dead(philos) == 1 || check_if_all_ate(philos) == 1)
			break ;
	return (pointer);
}
