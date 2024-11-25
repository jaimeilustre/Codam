// Assignment name  : epur_str
// Expected files   : epur_str.c
// Allowed functions: write
// --------------------------------------------------------------------------------

// Write a program that takes a string, and displays this string with exactly one
// space between words, with no spaces or tabs either at the beginning or the end,
// followed by a \n.

// A "word" is defined as a part of a string delimited either by spaces/tabs, or
// by the start/end of the string.

// If the number of arguments is not 1, or if there are no words to display, the
// program displays \n.

// Example:

// $> ./epur_str "See? It's easy to print the same thing" | cat -e
// See? It's easy to print the same thing$
// $> ./epur_str " this        time it      will     be    more complex  . " | cat -e
// this time it will be more complex .$
// $> ./epur_str "No S*** Sherlock..." "nAw S*** ShErLaWQ..." | cat -e
// $
// $> ./epur_str "" | cat -e
// $
// $>

// $> ./epur_str "vous voyez c'est facile d'afficher la meme chose" | cat -e
// vous voyez c'est facile d'afficher la meme chose$
// $> ./epur_str " seulement          la c'est      plus dur " | cat -e
// seulement la c'est plus dur$
// $> ./epur_str "comme c'est cocasse" "vous avez entendu, Mathilde ?" | cat -e
// $
// $> ./epur_str "" | cat -e
// $
// $>

#include <unistd.h>

int skip_whitespace(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

int write_word(char *str, int i)
{
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int main(int argc, char **argv)
{
	int i = 0;
	int	first_word = 1;

	if (argc == 2)
	{
		i = skip_whitespace(argv[1], i);
		while (argv[1][i])
		{
			if (!first_word)
				write (1, " ", 1);
			i = write_word(argv[1], i);
			first_word = 0;
			i = skip_whitespace(argv[1], i);
		}
	}
	write(1, "\n", 1);
	return (0);
}
