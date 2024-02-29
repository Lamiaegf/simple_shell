#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>


#define TOK_BUFSIZE 128
#define BUFSIZE 1024
#define  TOK_DELIM " \n\t\r\a"

/**
 * struct data - struct contains all relevant data
 * @argv: argument vector
 * @read: input from the users
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_env: environmrnt variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **argv;
	char *read;
	char **args;
	int status;
	int counter;
	char **_env;
	char *pid;
} data_sh;

/**
 * struct line_list - Single linked list to store command lines
 * @line: command line
 * @next: next node
 * Description: single linked list store command lines
 */
typedef struct line_list
{
	char *line;
	struct line_list *next;
} line_ls;

/**
 * struct spt_list - Single linled list to store separators
 * @sept: separators ; | &
 * @next: next node
 */
typedef struct spt_list
{
	char sept;
	struct spt_list *next;
} spt_ls;

/**
 * struct var_list - single linked list to store variables
 * @len_var: length of the variable
 * @vl: value of the variable
 * @len_vl: length of the value
 * @next: next node
 */
typedef struct var_list
{
	int len_var;
	char *vl;
	int len_vl;
	struct var_list *next;
} var_ls;

/**
 * struct built_in - builtin struct for command args.
 * @name: name of the command builtin
 * @f: pointer to function
 */
typedef struct built_in
{
	char *name;
	int (*f)(data_sh *datash);
} builtin_s;

/* Double pointer to an array of characters "environment" */
extern char **environ;

/* str_func1.c */
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, const char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);

/* str_func2.c */
int _strspn(char *s, char *receive);
int _strlen(const char *s);
void rev_string(char *s);
char *_strdup(const char *s);

/* str_func3.c */
int _isdigit(const char *s);
int cmp_chars(char s[], const char *d);
char *_strtok(char s[], const char *d);

/* mem_allocat.c */
void _memcpy(void *dest, const void *src, unsigned int size);
void *_realloc(void *p, unsigned int old_size, unsigned int new_size);
char **realloc_dp(char **p, unsigned int old_size, unsigned int new_size);

/* lists_func1.c */
line_ls *put_line_end(line_ls **head, char *line);
void free_line_list(line_ls **head);
spt_ls *put_spt_end(spt_ls **head, char spt);
void free_spt_list(spt_ls **head);

/* lists_func2.c */
var_ls *put_var_end(var_ls **head, int lvar, char *var, int lval);
void free_var_list(var_ls **head);

/* syntax_error.c */
int first_char(char *read, int *i);
int repeated_char(char *read, int i);
int error_spt_op(char *read, int i, char last);
void display_syntax_error(data_sh *datash, char *read, int i, int bool);
int check_syntax_error(data_sh *datash, char *read);

/* error_func1.c */
char *strcat_cd(data_sh *, char *, char *, char *);
char *error_cd(data_sh *datash);
char *error_not_found(data_sh *datash);
char *error_exit_shell(data_sh *datash);

/* error_func2.c */
char *error_env(data_sh *datash);
char *error_path(data_sh *datash);

/* get_func.c */
int get_error(data_sh *datash, int eval);
void get_sigint(int sig);
int get_help(data_sh *datash);
int (*get_builtin(char *cmd))(data_sh *datash);

/* system_calls.c */
char *read_line(int *edf);
void show_line(char **linef, size_t *m, char *buffer, size_t k);
ssize_t get_line(char **linef, size_t *m, FILE *stream);
int exec_line(data_sh *datash);

/* shell_loop.c */
char *no_comment(char *rd);
void sh_loop(data_sh *datash);

/* split.c */
char *swap_char(char *read, int bool);
void add_nodes(spt_ls **head_s, line_ls **head_l, char *read);
void _next(spt_ls **list_s, line_ls **list_l, data_sh *datash);
int split_cmds(data_sh *datash, char *read);
char **split_line(char *read);

/* r_var.c */
void check_env(var_ls **h, char *rd, data_sh *data);
int check_var(var_ls **h, char *rd, char *st, data_sh *data);
char *replaced_input(var_ls **head, char *read, char *new_input, int nlen);
char *rep_var(char *read, data_sh *datash);

/* exec_cmd.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_env);
int _executable(data_sh *datash);
int check_error_cmd(char *dir, data_sh *datash);
int cmd_exec(data_sh *datash);

/* env_func1.c */
int cmp_env_name(const char *nenv, const char *name);
char *_getenv(const char *name, char **_env);
int _env(data_sh *datash);
char *copy_data(char *name, char *value);

/* env_func2.c */
void set_env(char *name, char *value, data_sh *datash);
int _setenv(data_sh *datash);
int _unsetenv(data_sh *datash);

/* cd.c */
void cd_dot(data_sh *datash);
void cd_to(data_sh *datash);
void cd_back(data_sh *datash);
void cd_home(data_sh *datash);
int cd_sh(data_sh *datash);

/* _exit.c */
int exit_sh(data_sh *datash);

/* _stdlib.c */
int get_len(int m);
char *_itoa(int m);
int _atoi(char *rs);

/* help_func1.c */
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_general(void);
void help_exit(void);

/* help_func2.c */
void help(void);
void help_alias(void);
void help_cd(void);

#endif
