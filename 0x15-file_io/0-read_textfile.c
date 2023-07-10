#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
/**
 * read_textfile - reads a text file and prints it to the POSIX standard output
 * @filename: pointer to name of the file
 * @letters: the number of letters it should read and print
 *
 * Return: returns actual number of letters it could read and print
 * if the file can not be opened or read, return 0
 * if filename is NULL return 0
 * if write fails or does not write the expected amount of bytes, return 0
 */

ssize_t read_textfile(const char *filename, size_t letters)
{
	int FD;
	char *buff;
	ssize_t bytes_to_read;
	ssize_t bytes_to_write;


	if (filename == NULL)
		return (0);

	FD = open(filename, O_RDONLY);

	if (FD == -1)
		return (0);

	buff = malloc(sizeof(char) * letters);
	if (buff == NULL)
	{
		close(FD);
		return (0);
	}
	bytes_to_read = read(FD, buff, letters);
	close(FD);
	if (bytes_to_read == -1)
	{
		free(buff);
		return (0);
	}

	bytes_to_write = write(STDOUT_FILENO, buff, bytes_to_read);
	free(buff);

	if (bytes_to_write != bytes_to_read)
		return (0);
	return (bytes_to_write);
}
