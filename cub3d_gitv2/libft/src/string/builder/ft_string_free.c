#include "libft.h"
#include <stdlib.h>

/**
 * @brief Frees the memory allocated for a string and resets its properties.
 *
 * This function frees the memory allocated for the string `arg` and sets its
 * `str` pointer to NULL. It also resets the `capacity` and `index` properties
 * of the string to 0.
 *
 * @param arg The string to be freed.
 */
void	ft_string_free(t_string *arg)
{
	free(arg->content);
	arg->content = NULL;
	arg->capacity = 0;
	arg->index = 0;
}
