#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	if (dst_len >= size)
		return (size + src_len);
	ft_strlcpy(&dst[dst_len], (char *)src, size - dst_len);
	return (dst_len + src_len);
}
