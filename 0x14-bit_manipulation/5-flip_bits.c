#include "main.h"
/**
 * flip_bits - returns the number of bits you would need to flip
 * to get from one number to another
 * @n: number 1
 * @m: number 2
 *
 * Return: the number of bits you would need to flip
 */
unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
	unsigned long int exclusive;
	unsigned int count_bits = 0;

	exclusive = n ^ m;

	while (exclusive)
	{
		count_bits += exclusive & 1;
		exclusive = exclusive >> 1;
	}
	return (count_bits);
}
