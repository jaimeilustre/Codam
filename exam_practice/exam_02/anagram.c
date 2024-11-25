#include <stdio.h>
#include <string.h>

int	ft_strlen(char *str)
{
	int len = 0;

	while (str[len])
		len++;
	return (len);
}

int main(int argc, char **argv)
{
	char *s1 = argv[1];
	char *s2 = argv[2];
	int count1[256] = {0};
	int count2[256] = {0};
	int i = 0;
	
	if (argc == 3)
	{
		if (ft_strlen(s1) != ft_strlen(s2))
			return (1);
		while (s1[i])
		{
			if (s1[i] >= 'A' && s1[i] <= 'Z') // case insensitive; remove if not needed
				s1[i] += 32;
			count1[(unsigned char)s1[i]]++;
			i++;
		}
		i = 0;
		while (s2[i])
		{
			if (s2[i] >= 'A' && s2[i] <= 'Z') // case insensitive; remove if not needed
				s2[i] += 32;
			count2[(unsigned char)s2[i]]++;
			i++;
		}
		i = 0;
		while (i < 256)
		{
			if (count1[i] != count2[i])
				return (1);
			i++;
		}
	}
	return (0);
}
