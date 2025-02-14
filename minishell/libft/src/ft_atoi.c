/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:19:31 by jboon             #+#    #+#             */
/*   Updated: 2024/12/02 17:38:58 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*ft_trim_whitespaces(const char *nptr)
{
	while (*nptr && ft_strchr(" \f\n\r\t\v", *nptr))
		++nptr;
	return (nptr);
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
