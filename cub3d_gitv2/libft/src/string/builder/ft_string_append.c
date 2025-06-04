#include "libft.h"

/**
 * Appends a character to the given string.
 *
 * @param arg The string to append to.
 * @param c The character to append.
 * @return True if the character was successfully appended, false otherwise.
 */
bool	ft_string_append(t_string *arg, char c)
{
	if (arg->index == arg->capacity)
	{
		arg->capacity *= 2;
		arg->content = ft_realloc(arg->content, arg->index, arg->capacity);
		if (!arg->content)
			return (false);
	}
	arg->content[arg->index] = c;
	arg->index++;
	return (true);
}
