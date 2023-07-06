#include "main.h"
/**
 * set_bit - sets the value of a bit to 1 at a given index.
 * @n: pointer the number
 * @index: the index of the bit that we want to set to 1
 *
 * Return: 1 if it worked, or -1 if an error occurred
 */
int set_bit(unsigned long int *n, unsigned int index)
{
	unsigned long int bit_mask;

	if (index >= (sizeof(unsigned long int) * 8)) /* 64*/
		return (-1);

	bit_mask = 1UL << index;
	/* 1UL represents an unsigned long integer literal with a value of 1*/
	*n = *n | bit_mask;
	return (1);

}
