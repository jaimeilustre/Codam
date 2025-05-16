/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jilustre <jilustre@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/16 13:42:51 by jilustre      #+#    #+#                 */
/*   Updated: 2025/05/16 13:53:20 by jilustre      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	main(void)
{
	int				len_ft;
	int				len_std;
	char			c = 'j';
	char			*str = "Hello, World!";
	void			*ptr = str;
	int				nb = 0;
	unsigned int	unb = 42;

	// Testing %c (character)
	len_ft = ft_printf("%c\n", c);
	len_std = printf("%c\n", c);
	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

	// Testing %s (string)
	len_ft = ft_printf("%s\n", str);
	len_std = printf("%s\n", str);
	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

	// Testing if string is NULL
	len_ft = ft_printf("%s\n", NULL);
	len_std = printf("%s\n", (char *)NULL);
	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

	// Testing %p (pointer)
	len_ft = ft_printf("%p\n", ptr);
	len_std = printf("%p\n", ptr);
	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

	// Testing if pointer is NULL;
	len_ft = ft_printf("%p\n", NULL);
	len_std = printf("%p\n", NULL);
	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

	// Testing %d and %i (integer)
	len_ft = ft_printf("%d\n", nb);
	len_std = printf("%d\n", nb);
	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

	len_ft = ft_printf("%i\n", nb);
	len_std = printf("%i\n", nb);
	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

	// Testing %u (unsigned integer)
	len_ft = ft_printf("%u\n", unb);
	len_std = printf("%u\n", unb);
	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

	// Testing %x (hexadecimal, lowercase)
	len_ft = ft_printf("%x\n", unb);
	len_std = printf("%x\n", unb);
	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

	// Testing %X (hexadecimal, uppercase)
	len_ft = ft_printf("%X\n", unb);
	len_std = printf("%X\n", unb);
	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

	// Testing %% (percent sign)
	len_ft = ft_printf("%%\n");
	len_std = printf("%%\n");
	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

	// Testing multiple specifiers (different)
	len_ft = ft_printf("%c, %s, %p, %d, %x, %X\n", c, str, ptr, nb, unb, unb);
	len_std = printf("%c, %s, %p, %d, %x, %X\n", c, str, ptr, nb, unb, unb);
	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

	// Testing multiple specifiers (same)
	len_ft = ft_printf("%s, %s, %s, %s, %s\n", str, str, str, str, str);
	len_std = printf("%s, %s, %s, %s, %s\n", str, str, str, str, str);
	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

	// Testing NULL
	len_ft = ft_printf(NULL);
	len_std = printf(NULL);
	printf("My own: %d | Original: %d\n\n", len_ft, len_std);

	return (0);
}