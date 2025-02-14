/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:40:28 by jboon             #+#    #+#             */
/*   Updated: 2024/12/02 17:38:56 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "libft.h"

static int	is_int_overflow(size_t a, size_t b)
{
	if (b > 0 && a > SIZE_MAX / b)
		return (1);
	return (0);
}

void	*ft_calloc(size_t elements, size_t size)
{
	void	*ptr;

	if (is_int_overflow(elements, size))
		return (NULL);
	ptr = malloc(elements * size);
	if (ptr != NULL)
		ft_bzero(ptr, elements * size);
	return (ptr);
}
