#include "shell.h"

/**
 * _ForExiting - for exiting shell (get out)
 *
 * @INfor: Structure arguments
 *
 * -Return: write the exit msg
 */

int _ForExiting(info_t *INfor)
{
	int Chkexit;

	if (INfor->argv[1])
	{
		Chkexit = _ErroAotoi(INfor->argv[1]);
		if (Chkexit == -1)
		{
			INfor->status = 2;
			print_error(INfor, "Illegal number: ");
			_ErrPutos(INfor->argv[1]);
			_ErrPutochar('\n');
			return (1);
		}
		INfor->err_num = _ErroAotoi(INfor->argv[1]);
		return (-2);
	}
	INfor->err_num = -1;
	return (-2);
}

/**
 * _Chk_cdNow - for changing current directory
 *
 * @INfor: Structure arguments
 *
 * -Return: sucess only 0
 */

int _Chk_cdNow(info_t *INfor)
{
	char *s, *dir, buffer[1024];
	int chdir_reto;

	s = getcwd(buffer, 1024);
	if (!s)
		_PutPs("TODO: >>getcwd failure emsg here<<\n");
	if (!INfor->argv[1])
	{
		dir = _getenv(INfor, "HOME=");
		if (!dir)
			chdir_reto =
				chdir((dir = _getenv(INfor, "PWD=")) ? dir : "/");
		else
			chdir_reto = chdir(dir);
	}
	else if (_StrngCmpr(INfor->argv[1], "-") == 0)
	{
		if (!_getenv(INfor, "OLDPWD="))
		{
			_PutPs(s);
			_PutPcharc('\n');
			return (1);
		}
		_PutPs(_getenv(INfor, "OLDPWD=")), _PutPcharc('\n');
		chdir_reto =
			chdir((dir = _getenv(INfor, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_reto = chdir(INfor->argv[1]);
	if (chdir_reto == -1)
	{
		print_error(INfor, "can't cd to ");
		_ErrPutos(INfor->argv[1]), _ErrPutochar('\n');
	}
	else
	{
		_EnviroSetter(INfor, "OLDPWD", _getenv(INfor, "PWD="));
		_EnviroSetter(INfor, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _ForHelpNow - for changing the current directory (agian)
 *
 * @INfor: Structure arguments
 *
 * -Return: sucess only 0
 */

int _ForHelpNow(info_t *INfor)
{
	char **arg_array;

	arg_array = INfor->argv;
	_PutPs("help call works. Function not yet implemented \n");
	if (0)
		_PutPs(*arg_array);
	return (0);
}

