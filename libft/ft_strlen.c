/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimeilustre <jaimeilustre@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:48:33 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/16 07:13:27 by jaimeilustr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strlen(const char *s)
{
    size_t len;

	if (!s)
		return (0);
    len = 0;
    while(s[len])
        len++;
    return (len);
}

// #include <stdio.h>

// int main(void)
// {
//     char    *str = "Hello, world!";

//     printf("Length: %d\n", ft_strlen(str));
//     return (0);
// }