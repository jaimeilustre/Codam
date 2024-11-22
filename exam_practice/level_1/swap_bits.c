// Assignment name  : swap_bits
// Expected files   : swap_bits.c
// Allowed functions:
// --------------------------------------------------------------------------------

// Write a function that takes a byte, swaps its halves (like the example) and
// returns the result.

// Your function must be declared as follows:

// unsigned char	swap_bits(unsigned char octet);

// Example:

//   1 byte
// _____________
//  0100 | 0001
//      \ /
//      / \
//  0001 | 0100

#include <unistd.h>
#include <stdio.h>

unsigned char	swap_bits(unsigned char octet)
{
	return ((octet >> 4) | (octet << 4));
}
int	main(void)
{
	unsigned char test1 = 0b01000001; // 65 in decimal, binary: 01000001
	unsigned char test2 = 0b11110000; // 240 in decimal, binary: 11110000
	unsigned char test3 = 0b00001111; // 15 in decimal, binary: 00001111
	unsigned char test4 = 0b10101010; // 170 in decimal, binary: 10101010

	printf("Original: %02X, Swapped: %02X\n", test1, swap_bits(test1));
	printf("Original: %02X, Swapped: %02X\n", test2, swap_bits(test2));
	printf("Original: %02X, Swapped: %02X\n", test3, swap_bits(test3));
	printf("Original: %02X, Swapped: %02X\n", test4, swap_bits(test4));

	return (0);
}