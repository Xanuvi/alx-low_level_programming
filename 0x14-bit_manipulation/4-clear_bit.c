#include "main.h"
/**
 * clear_bit - function that sets the value of a bit to 0 at a given index
 * @n: pointer the number
 * @index:  is the index, starting from 0 of the bit you want to set
 *
 * Return: 1 if it worked, or -1 if an error occurred
 */
int clear_bit(unsigned long int *n, unsigned int index)
{
	unsigned long int bit_mask;

	if (index >= (sizeof(unsigned long int) * 8)) /* 64*/
		return (-1);

	bit_mask = 1UL << index;
	/* 1UL represents an unsigned long integer literal with a value of 1*/
	*n = *n & (~(bit_mask));
	return (1);

}
