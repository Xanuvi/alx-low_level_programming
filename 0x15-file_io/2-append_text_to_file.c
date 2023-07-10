#include "main.h"

/**
 * append_text_to_file - function that appends text at the end of a file
 * @filename: pointer to the name of the file
 * @text_content: the NULL terminated string to add at the end of the file
 *
 * Return: 1 on success, -1 on failure
 */
int append_text_to_file(const char *filename, char *text_content)
{
	int FD, len = 0, bytes_written;

	if (filename == NULL)
		return (-1);

	FD = open(filename, O_WRONLY | O_APPEND);
	if (FD == -1)
		return (-1);

	if (text_content != NULL)
	{
		while (text_content[len])
			len++;

		bytes_written = write(FD, text_content, len);
		if (bytes_written != len)
		{
			close(FD);
			return (-1);
		}
	}
	close(FD);
	return (1);
}
