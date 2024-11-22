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
	
	if (argc == 3)
	{
		if (ft_strlen(s1) != ft_strlen(s2))
			return (1);
		int count1[256] = {0};
		int count2[256] = {0};
		int i = 0;
		while (s1[i])
		{
			count1[(unsigned char)s1[i]]++;
			count2[(unsigned char)s2[i]]++;
			i++;
		}
		i = 0;
		while (i < 256)
		{
			if (count1[i] != count2[i])
			{
				printf("not anagram");
				return (0);
			}
			i++;
		}
	}
	printf("anagram");
	return (0);
}