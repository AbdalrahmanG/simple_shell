#include "shell.h"

/**
 * input_buf - for buffering the chained commands for shell
 *
 * @INfor: the used parameter struct
 * @buf: buffer address
 * @len: lnth vars address
 *
 * Return: ro
 */

ssize_t input_buf(info_t *INfor, char **buf, size_t *len)
{
	ssize_t ro = 0;
	size_t PoiLen = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, SnHandor);
#if USE_GETLINE
		ro = getline(buf, &PoiLen, stdin);
#else
		ro = _getline(INfor, buf, &PoiLen);
#endif
		if (ro > 0)
		{
			if ((*buf)[ro - 1] == '\n')
			{
				(*buf)[ro - 1] = '\0';
				ro--;
			}
			INfor->linecount_flag = 1;
			remove_comments(*buf);
			History_listBuilding(INfor, *buf, INfor->histcount++);
			{
				*len = ro;
				INfor->cmd_buf = buf;
			}
		}
	}
	return (ro);
}

/**
 * inputGitter - for getting line - newline
 *
 * @INfor:the used parameter struct
 *
 * Return: ro
 */

ssize_t inputGitter(info_t *INfor)
{
	static char *buf;
	static size_t io, jo, leno;
	ssize_t ro = 0;
	char **buf_p = &(INfor->arg), *p;

	_PutPcharc(BUFF_FRFLUSH);
	ro = input_buf(INfor, &buf, &leno);
	if (ro == -1)
		return (-1);
	if (leno)
	{
		jo = io;
		p = buf + io;

		ChkChain_again(INfor, buf, &jo, io, leno);
		while (jo < leno)
		{
			if (Chk_Chain(INfor, buf, &jo))
				break;
			jo++;
		}

		io = jo + 1;
		if (io >= leno)
		{
			io = leno = 0;
			INfor->TYPO_BUFF_CMD = CMD_NORM; /* just bear with me */
		}

		*buf_p = p;
		return (_StrngLnth(p));
	}

	*buf_p = buf;
	return (ro);
}

/**
 * buffr_Reading - for reading the buffer not the address
 *
 * @INfor: the used parameter struct
 * @buf: buffer of course
 * @i: tjos is the size
 *
 * Return: ro
 */

ssize_t buffr_Reading(info_t *INfor, char *buf, size_t *i)
{
	ssize_t ro = 0;

	if (*i)
		return (0);
	ro = read(INfor->readfile_Def, buf, BUFFR_READING_SIZE);
	if (ro >= 0)
		*i = ro;
	return (ro);
}

/**
 * _getline - fo geting next line input from this STDIN
 *
 * @INfor: th used parameter struct
 * @ptro: pointer address space
 * @length: size or lenth preallocated buff
 *
 * Return: so
 */

int _getline(info_t *INfor, char **ptro, size_t *length)
{
	static char buf[BUFFR_READING_SIZE];
	static size_t io, leno;
	size_t ko;
	ssize_t ro = 0, so = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptro;
	if (p && length)
		so = *length;
	if (io == leno)
		io = leno = 0;

	ro = buffr_Reading(INfor, buf, &leno);
	if (ro == -1 || (ro == 0 && leno == 0))
		return (-1);

	c = _strngCharc(buf + io, '\n');
	ko = c ? 1 + (unsigned int)(c - buf) : leno;
	new_p = _realloc(p, so, so ? so + ko : ko + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (so)
		_strngconc(new_p, buf + io, ko - io);
	else
		_Strgcop(new_p, buf + io, ko - io + 1);

	so += ko - io;
	io = ko;
	p = new_p;

	if (length)
		*length = so;
	*ptro = p;
	return (so);
}

/**
 * SnHandor - for blocking the usage of ctrl-C
 *
 * @sig_num: the used signa-number
 *
 * Return: void (nothing)
 */

void SnHandor(__attribute__((unused))int sig_num)
{
	_PutPs("\n");
	_PutPs("$ ");
	_PutPcharc(BUFF_FRFLUSH);
}

