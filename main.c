#include "shell.h"

/**
 * main - the entry point and the main file
 *
 * @ac: couted arguments
 * @av: counted arguments vector
 *
 * Return: sucess 0, fail 1
 */

int main(int ac, char **av)
{
	info_t INfor[] = {INFO_INIT};
	int file_Def = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(file_Def)
		: "r"(file_Def));

	if (ac == 2)
	{
		file_Def = open(av[1], O_RDONLY);
		if (file_Def == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_ErrPutos(av[0]);
				_ErrPutos(": 0: Can't open ");
				_ErrPutos(av[1]);
				_ErrPutochar('\n');
				_ErrPutochar(BUFF_FRFLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		INfor->readfile_Def = file_Def;
	}
	EnvoListFrPop(INfor);
	History_ReadingO(INfor);
	hshah(INfor, av);
	return (EXIT_SUCCESS);
}

