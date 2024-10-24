/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:50:44 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/10/24 16:44:37 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *str)
{
	unsigned long long	nb;
	int					sign;
	int					i;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (sign * nb);
}

int	ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/** @brief Destroys all the mutexes used in the program
 *  and handles error logging.
 *
 * @param str A string containing an error message to log
 *  (can be NULL).
 * @param program A pointer to the program structure, containing
 *  mutexes to destroy.
 * @param forks An array of mutexes representing forks used by philosophers.
 */
void	destroy_all(char *str, t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->dead_lock);
	while (i < program->philos[0].num_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

/** @brief This function repeatedly sleeps for 500 microseconds
 *  until the total sleep time
 * reaches the specified number of milliseconds.
 * 
 * @param milliseconds The number of milliseconds to sleep.
 * @return Always returns 0.
 */

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

/** @brief Gets the current time in milliseconds.
 * 
 * This function retrieves the current time using gettimeofday,
 * converts it to milliseconds, and returns the result.
 * 
 * @return The current time in milliseconds since the Epoch.
 */
size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
