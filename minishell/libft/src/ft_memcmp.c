/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:03:11 by jboon             #+#    #+#             */
/*   Updated: 2024/11/29 16:11:10 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*sa;
	const unsigned char	*sb;

	if (n == 0 || s1 == s2)
		return (0);
	i = 0;
	sa = (unsigned char *) s1;
	sb = (unsigned char *) s2;
	while (sa[i] == sb[i] && i < (n - 1))
		++i;
	return (sa[i] - sb[i]);
}
