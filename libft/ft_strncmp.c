/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilustre <jilustre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:53:27 by jilustre          #+#    #+#             */
/*   Updated: 2024/10/08 10:03:45 by jilustre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_strncmp(char *s1, char *s2, unsigned int n)
{
    unsigned int    i;

    i = 0;
    while (s1[i] && s2[i] && i < n)
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    if (i < n)
        return (s1[i] - s2[i]);
    return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	str1[] = "hello";
// 	char	str2[] = "Hello";
// 	char	str3[] = "long";
// 	char	str4[] = "longer";

// 	printf("%s, %s, %d\n", str1, str2, ft_strncmp(str1, str2, 1));
// 	printf("%s, %s, %d\n", str3, str4, ft_strncmp(str3, str4, 4));
// 	printf("%s, %s, %d\n", str3, str4, ft_strncmp(str3, str4, 5));
// 	return (0);
// }