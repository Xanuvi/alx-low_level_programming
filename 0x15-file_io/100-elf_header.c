#include "main.h"

/**
 * print_ident_info - Print the identification information.
 *
 * @ident: Pointer to the identification bytes.
 */
void print_ident_info(const unsigned char *ident)
{
	size_t i;

	printf("  Magic:   ");
	for (i = 0; i < sizeof(ident); ++i)
		printf("%02x ", ident[i]);
	printf("\n");
}

/**
 * print_class_info - Print the class information.
 *
 * @class: The class value.
 */
void print_class_info(unsigned char class)
{
	printf("  Class:                             ");
	switch (class)
	{
		case 1:
			printf("ELF32\n");
			break;
		case 2:
			printf("ELF64\n");
			break;
		default:
			printf("Invalid\n");
			break;
	}
}

/**
 * print_data_info - Print the data encoding information.
 *
 * @data: The data encoding value.
 */
void print_data_info(unsigned char data)
{
	printf("  Data:                              ");
	switch (data)
	{
		case 1:
			printf("2's complement, little endian\n");
			break;
		case 2:
			printf("2's complement, big endian\n");
			break;
		default:
			printf("Invalid\n");
			break;
	}
}

/**
 * print_osabi_info - Print the OS/ABI information.
 *
 * @osabi: The OS/ABI value.
 */
void print_osabi_info(unsigned char osabi)
{
	printf("  OS/ABI:                            ");

	switch (osabi)
	{
		case 0:
			printf("UNIX - System V\n");
			break;
		case 1:
			printf("HP-UX\n");
			break;
		case 2:
			printf("NetBSD\n");
			break;
		case 3:
			printf("Linux\n");
			break;
		case 6:
			printf("Solaris\n");
			break;
		case 7:
			printf("AIX\n");
			break;
		case 8:
			printf("IRIX\n");
			break;
		case 9:
			printf("FreeBSD\n");
			break;
		case 101:
			printf("GNU/Linux\n");  /*case for NetBSD*/
			break;
		default:
			printf("<unknown: %u>\n", osabi);
			break;
	}
}

/**
 * print_type_info - Print the object file type information.
 *
 * @type: The object file type value.
 */
void print_type_info(uint16_t type)
{
	printf("  Type:                              ");
	switch (type)
	{
		case 0:
			printf("No file type\n");
			break;
		case 1:
			printf("REL (Relocatable file)\n");
			break;
		case 2:
			printf("EXEC (Executable file)\n");
			break;
		case 3:
			printf("DYN (Shared object file)\n");
			break;
		case 4:
			printf("CORE (Core file)\n");
			break;
		default:
			printf("Invalid\n");
			break;
	}
}

/**
 * print_elf_header_info - Print the information contained in the ELF header.
 *
 * @header: Pointer to the ELF header structure.
 */
void print_elf_header_info(const Elf64_Ehdr *header)
{
	printf("ELF Header:\n");
	print_ident_info(header->ident);
	print_class_info(header->ident[4]);
	print_data_info(header->ident[5]);
	printf("  Version:                           %u (current)\n", header->ident[6]);
	print_osabi_info(header->ident[7]);
	printf("  ABI Version:                       %u\n", header->ident[8]);
	print_type_info(header->type);
	printf("  Entry point address:               0x%lx\n", header->entry);
}

/**
 * read_elf_header - Read the ELF header from the specified file.
 *
 * @filename: The name of the ELF file.
 *
 * Return: A pointer to the ELF header structure, or NULL on failure.
 */
Elf64_Ehdr *read_elf_header(const char *filename)
{
	int fd;
	Elf64_Ehdr *header = NULL;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "Error opening file: %s\n", strerror(errno));
		exit(ERROR_EXIT_CODE);
	}

	header = malloc(sizeof(Elf64_Ehdr));
	if (header == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(ERROR_EXIT_CODE);
	}

	if (read(fd, header, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr))
	{
		fprintf(stderr, "Error reading ELF header\n");
		free(header);
		exit(ERROR_EXIT_CODE);
	}

	close(fd);
	return (header);
}
/**
 * main - The entry point of the program.
 *
 * @argc: The number of command-line arguments.
 * @argv: An array of command-line argument strings.
 *
 * Return: 0 on success, or the error exit code on failure.
 */
int main(int argc, char *argv[])
{
	Elf64_Ehdr *header;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
		exit(ERROR_EXIT_CODE);
	}

	header = read_elf_header(argv[1]);
	print_elf_header_info(header);
	free(header);

	return (0);
}
