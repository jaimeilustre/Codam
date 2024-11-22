// Assignment name  : print_bits
// Expected files   : print_bits.c
// Allowed functions: write
// --------------------------------------------------------------------------------

// Write a function that takes a byte, and prints it in binary WITHOUT A NEWLINE
// AT THE END.

// Your function must be declared as follows:

// void	print_bits(unsigned char octet);

// Example, if you pass 2 to print_bits, it will print "00000010"

#include <unistd.h>
#include <stdio.h>

void	print_bits(unsigned char octet)
{
	int	i = 7;

	while (i >= 0)
	{
		if (octet & (1 << i))
			write(1, "1", 1);
		else
			write(1, "0", 1);
		i--;
	}
}

int	main(void)
{
	unsigned char test1 = 2;    // 00000010 in binary
	unsigned char test2 = 255;  // 11111111 in binary
	unsigned char test3 = 128;  // 10000000 in binary
	unsigned char test4 = 0;    // 00000000 in binary

	print_bits(test1);
	write(1, "\n", 1);  // Add a newline for readability
	print_bits(test2);
	write(1, "\n", 1);  // Add a newline for readability
	print_bits(test3);
	write(1, "\n", 1);  // Add a newline for readability
	print_bits(test4);
	write(1, "\n", 1);  // Add a newline for readability

	return (0);
}
