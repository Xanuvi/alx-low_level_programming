#include "main.h"
/**
 * get_bit - returns the value of a bit at a given index.
 * @n: the number
 * @index: the index of the bit
 *
 * Return: the value of the bit at index index or -1 if an error occured
 */
int get_bit(unsigned long int n, unsigned int index)
{
	unsigned long int bit_mask;

	if (index >= (sizeof(unsigned long int) * 8)) /* 64*/
		return (-1);

	bit_mask = 1UL << index;
	/* 1UL represents an unsigned long integer literal with a value of 1*/
	return ((n & bit_mask) ? 1 : 0);

}
