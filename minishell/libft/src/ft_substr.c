/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:49:35 by jboon             #+#    #+#             */
/*   Updated: 2024/12/02 17:38:56 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	s_len = 0;
	while (s[s_len])
		++s_len;
	if (start >= s_len)
		len = 0;
	else if (start + len > s_len)
		len = s_len - start;
	sub = malloc((len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	if (start < s_len)
		sub = ft_memcpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}
