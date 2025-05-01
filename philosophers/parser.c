/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/30 07:54:12 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/01 16:02:05 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "philo.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	valid_int(const char *str)
{
	while (*str == ' ')
		str++;
	if (*str == '-')
		return (0);
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
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

int	parse_args(char *arg)
{
	long	nb_long;
	int		nb;
	t_data	data;

	if (!valid_int(arg))
		return (-1);
	nb_long = ft_strtol(arg);
	nb = (int)nb_long;
	return (nb);
}

#include <stdio.h>

int main(void)
{
	char *arg = "21474836478";
	int	nb = parse_args(arg);
	if (!nb)
		return (-1);
	printf("%d\n", nb);
	return (0);
}
