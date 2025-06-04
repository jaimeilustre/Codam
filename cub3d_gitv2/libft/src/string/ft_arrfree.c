#include "libft.h"
#include <stdlib.h>

void	ft_arrfree(char **arr)
{
	size_t	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i]);
	free(arr);
}