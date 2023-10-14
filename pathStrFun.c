#include "shell.h"

/**
 * Chk_cmd - for determining file is executable command or not
 *
 * @INfor: the given INfor struct
 * @path: path it to the spicific file
 *
 * Return: success 1, otherwise 0
 */

int Chk_cmd(info_t *INfor, char *path)
{
	struct stat stro;

	(void)INfor;
	if (!path || stat(path, &stro))
		return (0);

	if (stro.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - for duplicating characters here
 *
 * @pathstr: the string pathed
 * @start: index of string here
 * @stop: stopping using fun. index
 *
 * Return: new buff poin
 */

char *dup_chars(char *pathstr, int start, int stop)
{
	static char bufff[1024];
	int io = 0, ko = 0;

	for (ko = 0, io = start; io < stop; io++)
		if (pathstr[io] != ':')
			bufff[ko++] = pathstr[io];
	bufff[ko] = 0;
	return (bufff);
}

/**
 * findMe_Path - for finding "cmd" in string path
 *
 * @INfor: the specific INfor struct
 * @pathstr: the sptring pathed
 * @cmd: our cmd to find and use
 *
 * Return: is "cmd" found or NULL
 */

char *findMe_Path(info_t *INfor, char *pathstr, char *cmd)
{
	int io = 0, My_Poss = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_StrngLnth(cmd) > 2) && Begin_By(cmd, "./"))
	{
		if (Chk_cmd(INfor, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[io] || pathstr[io] == ':')
		{
			path = dup_chars(pathstr, My_Poss, io);
			if (!*path)
				_StrngCat(path, cmd);
			else
			{
				_StrngCat(path, "/");
				_StrngCat(path, cmd);
			}
			if (Chk_cmd(INfor, path))
				return (path);
			if (!pathstr[io])
				break;
			My_Poss = io;
		}
		io++;
	}
	return (NULL);
}

