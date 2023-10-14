#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* _This for writting and reading comand_ */
#define BUFFR_READING_SIZE 1024
#define WRITE_BUFF_SSIZE 1024
#define BUFF_FRFLUSH -1

/* _This is for changing command_ */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3
#define WRITE_BUFF_SSIZE 1024


/* _This is for Con_verNum()_ */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* _if you are in system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr - for usign linked list
 *
 * @num: the field number that are used
 * @str: the used string
 * @next: next node pointer
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passINfor - for containing the pseudo-arguements passing
 * @arg: getline arguements string
 * @argv: arguments array that is used
 * @path: path string to used comment
 * @argc: the used count of argument
 * @line_count: the used counting error
 * @err_num: the used exit error code
 * @linecount_flag: flaged line input used
 * @fname: the used program filename
 * @env: the used linked list of nviron
 * @environ: for modifieing the copy of environm
 * @history: the used history nodde
 * @alias: the used alias here
 * @env_changed: when environment changed
 * @status: for returning status of exec'd command
 * @cmd_buf: for pointing to cmd_buf
 * @TYPO_BUFF_CMD: the used CMD_type ||, &&, ;
 * @readfile_Def: the used file_Def
 * @histcount: the used count pf history number
 */

typedef struct passINfor
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int TYPO_BUFF_CMD;
	int readfile_Def;
	int histcount;
} info_t;

#define INFO_INIT \
	{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - for containing builtin strin
 *
 * @type: builtin command
 * @func: the used function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* hshah.c */
int hshah(info_t *, char **);
int Find_myBuiltin(info_t *);
void figureCmd(info_t *);
void FunFork_cmd(info_t *);

/* pathStrFun.c */
int Chk_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *findMe_Path(info_t *, char *, char *);

/* loophshah.c */
int loophshah(char **);

/* estern_err.c */
void _ErrPutos(char *);
int _ErrPutochar(char);
int _putfile_Def(char c, int file_Def);
int _PutPsfile_Def(char *str, int file_Def);

/* strn_Err0.c */
int _StrngLnth(char *);
int _StrngCmpr(char *, char *);
char *Begin_By(const char *, const char *);
char *_StrngCat(char *, char *);
char *_StrnCpy(char *, char *);

char *_strDouble(const char *);
void _PutPs(char *);
int _PutPcharc(char);

char *_Strgcop(char *, char *, int);
char *_strngconc(char *, char *, int);
char *_strngCharc(char *, char);

char **strng_in2(char *, char *);
char **strng_in22(char *, char);

/* memFunToShll.c */
char *_memset(char *, char, unsigned int);
void DobyFree(char **);
void *_realloc(void *, unsigned int, unsigned int);

int FreeingPoin(void **);

/* helpfuncShll.c */
int SllInteractivate(info_t *);
int Chk_delim(char, char *);
int _ChkAlphap(int);
int _AtoiO(char *);

int _ErroAotoi(char *);
void print_error(info_t *, char *);
int print_dicm(int, int);
char *Con_verNum(long int, int, int);
void remove_comments(char *);

/* emu_builto.c */
int _ForExiting(info_t *);
int _Chk_cdNow(info_t *);
int _ForHelpNow(info_t *);

int _HistoryNow(info_t *);
int _myalias(info_t *);

/* line_getter. */
ssize_t inputGitter(info_t *);
int _getline(info_t *, char **, size_t *);
void SnHandor(int);

/* INfor.c */
void clear_INfor(info_t *);
void set_INfor(info_t *, char **);
void free_INfor(info_t *, int);

/* UsedEnvo.c */
char *_getenv(info_t *, const char *);
int _EnvoCuro(info_t *);
int _EnvoCuroiroSetter(info_t *);
int _EnvoCuroiroRemo(info_t *);
int EnvoListFrPop(info_t *);

char **EnviroGetter(info_t *);
int _EnviroRemo(info_t *, char *);
int _EnviroSetter(info_t *, char *, char *);

/* Filo_func.c */
char *HistoryGetter(info_t *INfor);
int History_Writingo(info_t *INfor);
int History_ReadingO(info_t *INfor);
int History_listBuilding(info_t *INfor, char *buf, int linecount);
int HistoryReNumb(info_t *INfor);

/* listAgain.c */
list_t *NodeAddetion(list_t **, const char *, int);
list_t *NodeAddetion_end(list_t **, const char *, int);
size_t List_ToBe_print_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

size_t List_lnth(const list_t *);
char **Conv_listTo_strn(list_t *);
size_t List_ToBe_print(const list_t *);
list_t *BeginsOf_node(list_t *, char *, char);
ssize_t index_yourNode(list_t *, list_t *);

/* ChainMine.c */
int Chk_Chain(info_t *, char *, size_t *);
void ChkChain_again(info_t *, char *, size_t *, size_t, size_t);
int AliasReplAlias(info_t *);
int VariaPlace(info_t *);
int StrngRep(char **, char *);

#endif

