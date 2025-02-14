/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboon <jboon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:21:17 by jboon             #+#    #+#             */
/*   Updated: 2024/12/03 15:33:08 by jboon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

/*
	Select the specifier based on c and write the output.
	@return The amount of printed characters. 0 if no specifier was found.
*/
static int	write_specifier(const char *c, int s_ln, t_format *f, va_list *args)
{
	char	*dst;
	int		len;

	len = 0;
	dst = NULL;
	if (*c == 'c')
		dst = ft_printf_char(va_arg(*args, int), f, &len);
	else if (*c == 's')
		dst = ft_printf_str(va_arg(*args, char *), f, &len);
	else if (*c == 'p')
		dst = ft_printf_ptr(va_arg(*args, void *), f, &len);
	else if (*c == 'x' || *c == 'X')
		dst = handle_hex(*c, va_arg(*args, unsigned int), f, &len);
	else if (*c == 'i' || *c == 'd')
		dst = ft_printf_int(va_arg(*args, int), f, &len);
	else if (*c == 'u')
		dst = handle_uint(va_arg(*args, unsigned int), f, &len);
	else if (*c == '%')
		return (write(STDOUT_FILENO, "%", 1));
	else
		return (write(STDOUT_FILENO, (c - 1), s_ln));
	if (dst == NULL)
		return (-1);
	len = write(STDOUT_FILENO, dst, len);
	return (free (dst), len);
}

/*
	Write the format to the output.
	On failure will print out the format string itself.
	@return Pointer s at the end of the format string.
*/
static const char	*write_next(const char *s, va_list *args, ssize_t *w_byte)
{
	const char	*start;
	ssize_t		bytes;
	t_format	f;

	start = s;
	s = ft_strchrnul(s, '%');
	bytes = write(STDOUT_FILENO, start, s - start);
	if (bytes == -1)
		return (*w_byte = -1, start);
	*w_byte += bytes;
	if (*s == '\0')
		return (s);
	s = ft_parse_format(++s, &f);
	bytes = write_specifier(s, (s - start) + 1, &f, args);
	if (bytes == -1)
		return (*w_byte = -1, s);
	*w_byte += bytes;
	return (++s);
}

/*
	Write formatted output to stdout.
	@return Successfull return, will return the amount of characters printed.
	@note
		Supports: flags(#0- +.), minumum width, and precision.

		Specifiers: %cspxXiud.

		No support: * or *n$.
*/
int	ft_printf(const char *s, ...)
{
	va_list		args;
	ssize_t		bytes;
	ssize_t		total;

	if (s == NULL)
		return (-1);
	total = 0;
	va_start(args, s);
	while (*s)
	{
		bytes = 0;
		s = write_next(s, &args, &bytes);
		if (bytes == -1)
		{
			total = -1;
			break ;
		}
		total += bytes;
	}
	va_end(args);
	return (total);
}
