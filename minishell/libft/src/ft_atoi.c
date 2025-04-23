/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboon <jboon@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/07 18:19:31 by jboon         #+#    #+#                 */
/*   Updated: 2025/04/09 01:37:13 by jboon         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <errno.h>
#include "libft.h"

static const char	*ft_trim_whitespaces(const char *nptr)
{
	while (*nptr && ft_strchr(" \f\n\r\t\v", *nptr))
		++nptr;
	return (nptr);
}

static const char	*ft_set_symbol(const char *nptr, int *symbol)
{
	*symbol = (*nptr != '-') - (*nptr == '-');
	nptr += (*nptr == '-' || *nptr == '+');
	return (nptr);
}

static const char	*ft_conv_nbr(const char *str, unsigned long *nbr, int sym)
{
	unsigned long	max;
	unsigned long	d;
	unsigned long	n;

	n = 0;
	max = LONG_MAX + (sym == -1);
	while (ft_isdigit(*str))
	{
		d = *str - '0';
		if ((n > 0 && max / n < 10) || max - (n * 10) < d)
		{
			n = max;
			errno = ERANGE;
			str = ft_strchr(str, '\0');
			break ;
		}
		n = n * 10 + d;
		++str;
	}
	*nbr = n * sym;
	return (str);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	symbol;

	result = 0;
	symbol = 1;
	nptr = ft_trim_whitespaces(nptr);
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			symbol = -1;
		++nptr;
	}
	while (*nptr && ft_isdigit(*nptr))
	{
		result = result * 10 + (*nptr - '0');
		++nptr;
	}
	return (result * symbol);
}

long	ft_strtol(const char *nptr, char **endptr)
{
	unsigned long	nbr;
	const char		*str;
	int				sym;

	nbr = 0;
	sym = 1;
	str = ft_trim_whitespaces(nptr);
	str = ft_set_symbol(str, &sym);
	if (!ft_isdigit(*str) && endptr != NULL)
	{
		errno = EINVAL;
		return (*endptr = (char *)nptr, nbr);
	}
	str = ft_conv_nbr(str, &nbr, sym);
	if (endptr != NULL)
		*endptr = (char *)str;
	return (nbr);
}
