#include "shell.h"

/**
 * HistoryGetter - for geting the history_file
 *
 * @INfor: the used parameter struct
 *
 * Return: stringo
 */

char *HistoryGetter(info_t *INfor)
{
	char *buf, *dir;

	dir = _getenv(INfor, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_StrngLnth(dir) + _StrngLnth(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_StrnCpy(buf, dir);
	_StrngCat(buf, "/");
	_StrngCat(buf, HIST_FILE);
	return (buf);
}

/**
 * History_Writingo - for creating new-file
 *
 * @INfor: the used parameter struct
 *
 * Return: when success 1, otherwise -1
 */

int History_Writingo(info_t *INfor)
{
	ssize_t file_Def;
	char *filename = HistoryGetter(INfor);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	file_Def = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (file_Def == -1)
		return (-1);
	for (node = INfor->history; node; node = node->next)
	{
		_PutPsfile_Def(node->str, file_Def);
		_putfile_Def('\n', file_Def);
	}
	_putfile_Def(BUFF_FRFLUSH, file_Def);
	close(file_Def);
	return (1);
}

/**
 * History_ReadingO - for reading history from file to another
 *
 * @INfor: the used parameter struct
 *
 * Return: succuess count, otherwise 0
 */

int History_ReadingO(info_t *INfor)
{
	int io, lastio = 0, linecnt = 0;
	ssize_t file_Def, rodylen, frosize = 0;
	struct stat stro;
	char *buf = NULL, *filename = HistoryGetter(INfor);

	if (!filename)
		return (0);

	file_Def = open(filename, O_RDONLY);
	free(filename);
	if (file_Def == -1)
		return (0);
	if (!fstat(file_Def, &stro))
		frosize = stro.st_size;
	if (frosize < 2)
		return (0);
	buf = malloc(sizeof(char) * (frosize + 1));
	if (!buf)
		return (0);
	rodylen = read(file_Def, buf, frosize);
	buf[frosize] = 0;
	if (rodylen <= 0)
		return (free(buf), 0);
	close(file_Def);
	for (io = 0; io < frosize; io++)
		if (buf[io] == '\n')
		{
			buf[io] = 0;
			History_listBuilding(INfor, buf + lastio, linecnt++);
			lastio = io + 1;
		}
	if (lastio != io)
		History_listBuilding(INfor, buf + lastio, linecnt++);
	free(buf);
	INfor->histcount = linecnt;
	while (INfor->histcount-- >= HIST_MAX)
		delete_node_at_index(&(INfor->history), 0);
	HistoryReNumb(INfor);
	return (INfor->histcount);
}

/**
 * History_listBuilding - for adding entry point at history list
 *
 * @INfor: Structure arguments
 * @buf: buffer that is used
 * @linecnt: the listed history
 *
 * Return: sucess only 0
 */

int History_listBuilding(info_t *INfor, char *buf, int linecnt)
{
	list_t *node = NULL;

	if (INfor->history)
		node = INfor->history;
	NodeAddetion_end(&node, buf, linecnt);

	if (!INfor->history)
		INfor->history = node;
	return (0);
}

/**
 * HistoryReNumb - for renumbering history lists after making changes
 *
 * @INfor: Structure arguments
 *
 * Return: mnew-count
 */

int HistoryReNumb(info_t *INfor)
{
	list_t *node = INfor->history;
	int io = 0;

	while (node)
	{
		node->num = io++;
		node = node->next;
	}
	return (INfor->histcount = io);
}

