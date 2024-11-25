// Assignment name  : rev_wstr
// Expected files   : rev_wstr.c
// Allowed functions: write, malloc, free
// --------------------------------------------------------------------------------

// Write a program that takes a string as a parameter, and prints its words in 
// reverse order.

// A "word" is a part of the string bounded by spaces and/or tabs, or the 
// begin/end of the string.

// If the number of parameters is different from 1, the program will display 
// '\n'.

// In the parameters that are going to be tested, there won't be any "additional" 
// spaces (meaning that there won't be additionnal spaces at the beginning or at 
// the end of the string, and words will always be separated by exactly one space).

// Examples:

// $> ./rev_wstr "You hate people! But I love gatherings. Isn't it ironic?" | cat -e
// ironic? it Isn't gatherings. love I But people! hate You$
// $>./rev_wstr "abcdefghijklm"
// abcdefghijklm
// $> ./rev_wstr "Wingardium Leviosa" | cat -e
// Leviosa Wingardium$
// $> ./rev_wstr | cat -e
// $
// $>

#include <unistd.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_putstr(char *str, int len)
{
	int i = 0;

	while (i < len)
	{
		ft_putchar(str[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
	int i = 0;
	int end;
	char *str = argv[1];

	if (argc == 2)
	{
		while(str[i])
			i++;
		end = i;
		while (end > 0)
		{
			while (end > 0 && (str[end - 1] == ' ' || str[end - 1] == '\t'))
				end--;
			int start = end;
			while (start > 0 && str[start - 1] != ' ' && str[start - 1] != '\t')
				start--;
			if (start < end)
			{
				ft_putstr(&str[start], end - start);
				if (start > 0)
					ft_putchar(' ');
			}
			end = start;
		}

	}
	ft_putchar('\n');
	return (0);
}