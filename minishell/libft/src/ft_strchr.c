/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:43:13 by jboon             #+#    #+#             */
/*   Updated: 2024/10/15 11:15:51 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	char	find;

	find = (char)c;
	while (*s && *s != find)
		++s;
	if (*s == find)
		return ((char *)s);
	return (NULL);
}
