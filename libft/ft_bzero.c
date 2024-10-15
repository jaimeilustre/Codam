/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilustre <jilustre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:46:46 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/15 16:06:15 by jilustre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
	return ;
}

// #include <stdio.h>

// int	main(void)
// {
// 	char str[3] = {"abc"};

// 	ft_bzero(str, 2);

// 	int i;
// 	i = 0;
// 	while (i < 3)
// 	{
// 		printf("%c", str[i]);
// 		i++;
// 	}
// 	return (0);
// }