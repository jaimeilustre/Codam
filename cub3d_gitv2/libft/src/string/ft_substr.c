#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	str_len;
	size_t	length;
	char	*str;

	if (s == NULL)
		return (NULL);
	if (len == 0)
		return (ft_strdup("\0"));
	if (start >= ft_strlen(s))
		return (ft_strdup("\0"));
	str_len = ft_strlen(&s[start]);
	if (str_len < len)
		length = str_len + 1;
	else
		length = len + 1;
	str = (char *)ft_calloc(length, sizeof(char));
	if (str == NULL)
		return (0);
	ft_strlcpy(str, &((char *)s)[start], length);
	return (str);
}
