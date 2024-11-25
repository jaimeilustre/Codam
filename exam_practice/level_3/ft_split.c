// Assignment name  : ft_split
// Expected files   : ft_split.c
// Allowed functions: malloc
// --------------------------------------------------------------------------------

// Write a function that takes a string, splits it into words, and returns them as
// a NULL-terminated array of strings.

// A "word" is defined as a part of a string delimited either by spaces/tabs/new
// lines, or by the start/end of the string.

// Your function must be declared as follows:

// char    **ft_split(char *str);

#include <stdlib.h>
#include <stdio.h>

int count_words(char *str)
{
	int i = 0;
	int word_count = 0;
	
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	while (str[i])
	{
		word_count++;
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			i++;
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;	
	}
	return (word_count);
}

int word_len(char *str)
{
	int i = 0;

	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		i++;
	return (i);
}

char *allocate_word(char *str)
{
	int i = 0;
	int len = word_len(str);
	char *word = malloc(len + 1);
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

void fill_words(char **array, char *str)
{
	int i = 0;
	int word_index = 0;

	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	while (str[i])
	{
		array[word_index] = allocate_word(&str[i]);
		word_index++;
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			i++;
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
	}
}

char **ft_split(char *str)
{
	int nb_words = count_words(str);
	char **array = malloc(sizeof(char *) * (nb_words + 1));
	if (!array)
		return (NULL);
	fill_words(array, str);
	array[nb_words] = 0;
	return (array);
}


int main(void)
{
	char *str = "Hello world, this is a test!";
	char **result = ft_split(str);

	for (int i = 0; result[i]; i++)
		printf("%s\n", result[i]);

	// Free allocated memory
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);

	return (0);
}
