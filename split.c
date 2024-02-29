#include "main.h"

/**
 * swap_char - swaps | and & for non-printed chars
 * @read: read string
 * @bool: type of swap
 * Return: swapped string
 */
char *swap_char(char *read, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; read[i]; i++)
		{
			if (read[i] == '|')
			{
				if (read[i + 1] != '|')
					read[i] = 16;
				else
					i++;
			}

			if (read[i] == '&')
			{
				if (read[i + 1] != '&')
					read[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; read[i]; i++)
		{
			read[i] = (read[i] == 16 ? '|' : read[i]);
			read[i] = (read[i] == 12 ? '&' : read[i]);
		}
	}
	return (read);
}

/**
 * add_nodes - add separators and command lines in the lists
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @read: read string
 * Return: no return
 */
void add_nodes(spt_ls **head_s, line_ls **head_l, char *read)
{
	int i;
	char *line;

	read = swap_char(read, 0);

	for (i = 0; read[i]; i++)
	{
		if (read[i] == ';')
			put_spt_end(head_s, read[i]);

		if (read[i] == '|' || read[i] == '&')
		{
			put_spt_end(head_s, read[i]);
			i++;
		}
	}

	line = _strtok(read, ";|&");
	do {
		line = swap_char(line, 1);
		put_line_end(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * _next - go to the next command line stored
 * @list_s: separator list
 * @list_l: command line list
 * @datash: data structure
 * Return: no return
 */
void _next(spt_ls **list_s, line_ls **list_l, data_sh *datash)
{
	int loop_sep;
	spt_ls *ls_s;
	line_ls *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (ls_s->sept == '&' || ls_s->sept == ';')
				loop_sep = 0;
			if (ls_s->sept == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->sept == '|' || ls_s->sept == ';')
				loop_sep = 0;
			if (ls_s->sept == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_cmds - splits command lines according to
 * the separators ;, | and &, and executes them.
 * @datash: data structure
 * @read: read string
 * Return: 0 to exit, 1 to continue
 */
int split_cmds(data_sh *datash, char *read)
{

	spt_ls *head_s, *list_s;
	line_ls *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, read);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->read = list_l->line;
		datash->args = split_line(datash->read);
		loop = exec_line(datash);
		free(datash->args);

		if (loop == 0)
			break;

		_next(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_spt_list(&head_s);
	free_line_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - tokenizes the input string
 * @read: read string.
 * Return: string splitted.
 */
char **split_line(char *read)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(read, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = realloc_dp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}
