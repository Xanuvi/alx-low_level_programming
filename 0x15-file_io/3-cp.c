#include "main.h"

/**
 * copy_file - Copies the content of file_from to file_to.
 * Returns 0 on success, -1 on error.
 */
int copy_file(const char *file_from, const char *file_to)
{
	int fd_from, fd_to;
	ssize_t nread;
	char buf[1024];

	fd_from = open(file_from, O_RDONLY);
	if (fd_from == -1) 
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file_from);
		return (-1);
	}
	fd_to = open(file_to, O_WRONLY | O_CREAT | O_TRUNC, 0664);/*rw-rw-r--*/
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file_to);
		close(fd_from);
		return (-1);
	}
	while ((nread = read(fd_from, buf, 1024)) > 0) 
	{
		if (write(fd_to, buf, nread) != nread) 
		{
			dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file_to);
			close(fd_from);
			close(fd_to);
			return (-1);
		}
	}
	if (nread == -1) 
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file_from);
		close(fd_from);
		close(fd_to);
		return (-1);
	}
	if (close(fd_from) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_from);
		return (-1);
	}
	if (close(fd_to) == -1) 
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_to);
		return (-1);
	}
	return (0);
}

/**
 * main - program that copies the content of a file to another file.
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: 0 on success, or an error code on failure
 */
int main(int argc, char **argv) 
{
	const char *file_from, *file_to;
	if (argc != 3) 
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		return (97);
	}
	file_from = argv[1];
	file_to = argv[2];
    /* Copy the file*/
	if (copy_file(file_from, file_to) == -1) 
	{
		return (99);
	}
	return 0;
}
