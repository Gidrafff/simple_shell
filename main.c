#include "shell.h"

/**
 * main - Entry point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 if success, otherwise 1 if error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int filedescriptor = 2;

	asm volatile ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (filedescriptor)
			: "r" (filedescriptor));

	if (ac == 2)
	{
		filedescriptor = open(av[1], O_RDONLY);
		if (filedescriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = filedescriptor;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
