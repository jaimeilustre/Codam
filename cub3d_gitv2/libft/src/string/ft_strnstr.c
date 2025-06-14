#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(needle);
	if (needle[i] == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (len > 0 && haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			if (len < j)
				break ;
			if (ft_strncmp(&haystack[i], needle, j) == 0)
				return ((char *)&haystack[i]);
		}
		len--;
		i++;
	}
	return (0);
}
