#include "shell.h"

/**
 * hshah - that is main shell loop from entry point
 *
 * @INfor: the used  parameter and return INfor struct
 * @av: vector argument
 *
 * Return: success 0,otherwise 1
 */

int hshah(info_t *INfor, char **av)
{
	ssize_t roo = 0;
	int builtin_reto = 0;

	while (roo != -1 && builtin_reto != -2)
	{
		clear_INfor(INfor);
		if (SllInteractivate(INfor))
			_PutPs("$ ");
		_ErrPutochar(BUFF_FRFLUSH);
		roo = inputGitter(INfor);
		if (roo != -1)
		{
			set_INfor(INfor, av);
			builtin_reto = Find_myBuiltin(INfor);
			if (builtin_reto == -1)
				figureCmd(INfor);
		}
		else if (SllInteractivate(INfor))
			_PutPcharc('\n');
		free_INfor(INfor, 0);
	}
	History_Writingo(INfor);
	free_INfor(INfor, 1);
	if (!SllInteractivate(INfor) && INfor->status)
		exit(INfor->status);
	if (builtin_reto == -2)
	{
		if (INfor->err_num == -1)
			exit(INfor->status);
		exit(INfor->err_num);
	}
	return (builtin_reto);
}

/**
 * Find_myBuiltin - for finding builtin commands
 *
 * @INfor: the used parameter
 *
 * Return: -1 when not found,0 when success
 *			1 when not successful, -2 when exit()
 */

int Find_myBuiltin(info_t *INfor)
{
	int io, built_in_reto = -1;
	builtin_table builtintbl[] = {
		{"exit", _ForExiting},
		{"env", _EnvoCuro},
		{"help", _ForHelpNow},
		{"history", _HistoryNow},
		{"EnviroSetter", _EnvoCuroiroSetter},
		{"EnviroRemo", _EnvoCuroiroRemo},
		{"cd", _Chk_cdNow},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (io = 0; builtintbl[io].type; io++)
		if (_StrngCmpr(INfor->argv[0], builtintbl[io].type) == 0)
		{
			INfor->line_count++;
			built_in_reto = builtintbl[io].func(INfor);
			break;
		}
	return (built_in_reto);
}

/**
 * figureCmd - for finding command in a specific path
 *
 * @INfor: the used parameter
 *
 * Return: void (nothing)
 */

void figureCmd(info_t *INfor)
{
	char *path = NULL;
	int io, ko;

	INfor->path = INfor->argv[0];
	if (INfor->linecount_flag == 1)
	{
		INfor->line_count++;
		INfor->linecount_flag = 0;
	}
	for (io = 0, ko = 0; INfor->arg[io]; io++)
		if (!Chk_delim(INfor->arg[io], " \t\n"))
			ko++;
	if (!ko)
		return;

	path = findMe_Path(INfor, _getenv(INfor, "PATH="), INfor->argv[0]);
	if (path)
	{
		INfor->path = path;
		FunFork_cmd(INfor);
	}
	else
	{
		if ((SllInteractivate(INfor) || _getenv(INfor, "PATH=")
			|| INfor->argv[0][0] == '/') && Chk_cmd(INfor, INfor->argv[0]))
			FunFork_cmd(INfor);
		else if (*(INfor->arg) != '\n')
		{
			INfor->status = 127;
			print_error(INfor, "not found\n");
		}
	}
}

/**
 * FunFork_cmd - for forking executing thread to run cmd
 *
 * @INfor: the used parameter
 *
 * Return: void (nothing)
 */

void FunFork_cmd(info_t *INfor)
{
	pid_t young_childPid;

	young_childPid = fork();
	if (young_childPid == -1)
	{
		perror("Error:");
		return;
	}
	if (young_childPid == 0)
	{
		if (execve(INfor->path, INfor->argv, EnviroGetter(INfor)) == -1)
		{
			free_INfor(INfor, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(INfor->status));
		if (WIFEXITED(INfor->status))
		{
			INfor->status = WEXITSTATUS(INfor->status);
			if (INfor->status == 126)
				print_error(INfor, "Permission denied\n");
		}
	}
}

