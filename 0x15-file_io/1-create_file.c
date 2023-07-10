#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

/**
 * create_file - function that creates a file.
 * @filename: is the name of the file to create
 * @text_content: is a NULL terminated string to write to the file
 *
 * Return: 1 on success, -1 on failure
 */
int create_file(const char *filename, char *text_content)
{
	int FD, bytes_to_write = 0;

	if (filename == NULL)
		return (0);
/*The created file must have those permissions: rw-------.*/
/*If the file already exists, do not change the permissions.*/
	FD = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (FD == -1)
		return (-1);
	if (text_content != NULL)
	{
		while (text_content[bytes_to_write] != '\0')
			bytes_to_write++;
		if (write(FD, text_content, bytes_to_write) != bytes_to_write)
		{
			close(FD);
			return (-1);
		}
	}
	close(FD);
	return (1);
}
