/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:52:39 by jboon             #+#    #+#             */
/*   Updated: 2024/10/15 11:17:15 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;
	char		find;

	last = NULL;
	find = (char)c;
	while (*s)
	{
		if (*s == find)
			last = s;
		++s;
	}
	if (*s == find)
		return ((char *)s);
	return ((char *)last);
}
