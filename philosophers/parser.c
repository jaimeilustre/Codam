/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/30 07:54:12 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/02 14:12:15 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#include "philo.h"

static bool	valid_int(const char *str)
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

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = c;
		i++;
	}
	return (s);
}

bool	parse_args(char *arg, int index, t_data *data)
{
	long	nb_long;

	if (!valid_int(arg))
		return (false);
	nb_long = ft_strtol(arg);
	if (nb_long > INT_MAX || nb_long <= 0)
		return (false);
	if (index == 0)
		data->nb_of_philos = (int)nb_long;
	else if (index == 1)
		data->time_to_die = (int)nb_long;
	else if (index == 2)
		data->time_to_eat = (int)nb_long;
	else if (index == 3)
		data->time_to_sleep = (int)nb_long;
	else if (index == 4)
		data->nb_of_meals_per_philo = (int)nb_long;
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc >= 5 && argc <= 6)
	{
		ft_memset(&data, 0, sizeof(t_data));
		i = 0;
		while (i < argc - 1)
		{
			if (!parse_args(argv[i + 1], i, &data))
				return (-1);
			i++;
		}
		if (argc == 5)
			data.nb_of_meals_per_philo = -1;
	}
	else if (argc <= 4)
		printf("Too few arguments\n");
	else
		printf("Too many arguments\n");
	return (0);
}
