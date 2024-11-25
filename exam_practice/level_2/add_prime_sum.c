// Assignment name  : add_prime_sum
// Expected files   : add_prime_sum.c
// Allowed functions: write, exit
// --------------------------------------------------------------------------------

// Write a program that takes a positive integer as argument and displays the sum
// of all prime numbers inferior or equal to it followed by a newline.

// If the number of arguments is not 1, or the argument is not a positive number,
// just display 0 followed by a newline.

// Yes, the examples are right.

// Examples:

// $>./add_prime_sum 5
// 10
// $>./add_prime_sum 7 | cat -e
// 17$
// $>./add_prime_sum | cat -e
// 0$
// $>

#include <unistd.h>

int	ft_atoi(char *str)
{
	int n = 0;

	while (*str)
	{
		n = n * 10 + *str -'0';
		str++;
	}
	return (n);
}

void ft_putnbr(int nb)
{
	if (nb > 9)
		ft_putnbr(nb / 10);
	char digit = nb % 10 + '0';
	write(1, &digit, 1);
}

int is_prime(int nb)
{
	int i = 2;
	while (i < nb)
	{
		if (nb % i == 0)
			return (0);
		i++;
	}
	return (1);
}

int add_prime_sum(int n)
{
	int i = 2;
	int sum = 0;

	while (i <= n)
	{
		if (is_prime(i))
			sum += i;
		i++;
	}
	return (sum);
}

int main(int argc, char **argv)
{
	int n = ft_atoi(argv[1]);

	if (argc == 2 && n)
		ft_putnbr(add_prime_sum(n));
	else
		ft_putnbr(0);
	write(1, "\n", 1);
	return (0);
}