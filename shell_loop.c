#include "main.h"

/**
 * no_comment - deletes comments from the input
 * @rd: read string
 * Return: input no  comments
 */
char *no_comment(char *rd)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; rd[i]; i++)
	{
		if (rd[i] == '#')
		{
			if (i == 0)
			{
				free(rd);
				return (NULL);
			}

			if (rd[i - 1] == ' ' || rd[i - 1] == '\t' || rd[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		rd = _realloc(rd, i, up_to + 1);
		rd[up_to] = '\0';
	}

	return (rd);
}

/**
 * sh_loop - Loop of shell
 * @datash: data relevant (argv, read, args)
 * Return: no return.
 */
void sh_loop(data_sh *datash)
{
	int loop, edf;
	char *read;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "$$ ", 4);
		read = read_line(&edf);
		if (edf != -1)
		{
			read = no_comment(read);
			if (read == NULL)
				continue;

			if (check_syntax_error(datash, read) == 1)
			{
				datash->status = 2;
				free(read);
				continue;
			}
			read = rep_var(read, datash);
			loop = split_cmds(datash, read);
			datash->counter += 1;
			free(read);
		}
		else
		{
			loop = 0;
			free(read);
		}
	}
}
