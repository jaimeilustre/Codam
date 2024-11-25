// Assignment name  : biggest_pal
// Expected files   : *.c, *.h
// Allowed functions: write
// --------------------------------------------------------------------------------

// Write a program named biggest_pal that takes a string as argument and prints the
// biggest palindrome included inside this string, followed by a newline.

// This string contains only lowercase characters.

// If there is two palindromes of the same length, you have to print the last one.

// If there is more or less than 1 argument, your program must print only a newline
// only.

// Exemples:

// $> biggest_pal "abcba"
// abcba
// $> biggest_pal "aaaaaaaaaabbcbbaaaa"
// aaaabbcbbaaaa
// $> biggest_pal "aooibdaoiwhoihwdoinzeldaisaboyobasiadlezfdsfnslk"
// zeldaisaboyobasiadlez
// $> biggest_pal "aeibaabaammaabaalek"
// aabaammaabaa
// $> biggest_pal abeb qpinqwjobo qkmnwoiq

// $> biggest_pal

// $>

#include <unistd.h>

int	ft_strlen(char *str)
{
	int len = 0;

	while (str[len])
		len++;
	return (len);
}

int	is_palindrome(char *str, int start, int end)
{
	while (start < end)
	{
		if (str[start] != str[end])
			return (0);
		start++;
		end--;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int i = 0;
	int max_len = 0;
	int start_index = 0;
	int str_len = ft_strlen(argv[1]);

	if (argc == 2)
	{
		while (i < str_len)
		{
			int j = i;
			while (j < str_len)
			{
				if (is_palindrome(argv[1], i, j))
				{
					int len = j - i + 1;
					if (len > max_len || (len == max_len && i > start_index))
					{
						max_len = len;
						start_index = i;
					}
				}
				j++;
			}
			i++;
		}
		write (1, argv[1] + start_index, max_len);
	}
	write(1, "\n", 1);
	return (0);
}

//Finding the shortest palindrome

#include <unistd.h>
#include <limits.h>

int	ft_strlen(char *str)
{
	int len = 0;

	while (str[len])
		len++;
	return (len);
}

int	is_palindrome(char *str, int start, int end)
{
	while (start < end)
	{
		if (str[start] != str[end])
			return (0);
		start++;
		end--;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int i = 0;
	int min_len = INT_MAX;
	int start_index = 0;
	int str_len = ft_strlen(argv[1]);

	if (argc == 2)
	{
		while (i < str_len)
		{
			int j = i;
			while (j < str_len)
			{
				if (is_palindrome(argv[1], i, j))
				{
					int len = j - i + 1;
					if (len < min_len || (len == min_len && i < start_index))
					{
						min_len = len;
						start_index = i;
					}
				}
				j++;
			}
			i++;
		}
		write (1, argv[1] + start_index, min_len);
	}
	write(1, "\n", 1);
	return (0);
}