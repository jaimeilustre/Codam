/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/08 16:13:36 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/15 10:45:00 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

#include "philo.h"

/*Checks for valid int*/
bool	valid_int(const char *str)
{
	while (*str == ' ')
		str++;
	if (*str == '-')
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (false);
		str++;
	}
	return (true);
}

/*Convers string to long type*/
long	ft_strtol(const char *nptr)
{
	int			i;
	int			sign;
	long		nb;

	nb = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		if (nb > INT_MAX && sign == 1)
			return (LONG_MAX);
		if (nb > (long)INT_MAX + 1 && sign == -1)
			return (LONG_MIN);
		i++;
	}
	return (nb * sign);
}

/*Get current time in milliseconds*/
size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/*Improved version of usleep*/
int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < ms)
		usleep(500);
	return (0);
}

/*Prints message for each part of the routine*/
void	print_message(t_philo *philo, char *msg)
{
	size_t	timestamp;

	sem_wait(philo->data->print_sem);
	timestamp = get_current_time() - philo->data->start_time;
	printf("%lu %d %s\n", timestamp, philo->id, msg);
	sem_post(philo->data->print_sem);
}
