#include "main.h"

/**
 * check_env - checks if the typed variable is an env variable
 * @h: head of linked list
 * @rd: read string
 * @data: data structure
 * Return: no return
 */
void check_env(var_ls **h, char *rd, data_sh *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->_env;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				put_var_end(h, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (rd[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; rd[j]; j++)
	{
		if (rd[j] == ' ' || rd[j] == '\t' || rd[j] == ';' || rd[j] == '\n')
			break;
	}

	put_var_end(h, j, NULL, 0);
}

/**
 * check_var - check if the typed variable $$ or $?
 * @h: head of the linked list
 * @rd: read string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int check_var(var_ls **h, char *rd, char *st, data_sh *data)
{
	int i, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (i = 0; rd[i]; i++)
	{
		if (rd[i] == '$')
		{
			if (rd[i + 1] == '?')
				put_var_end(h, 2, st, lst), i++;
			else if (rd[i + 1] == '$')
				put_var_end(h, 2, data->pid, lpd), i++;
			else if (rd[i + 1] == '\n')
				put_var_end(h, 0, NULL, 0);
			else if (rd[i + 1] == '\0')
				put_var_end(h, 0, NULL, 0);
			else if (rd[i + 1] == ' ')
				put_var_end(h, 0, NULL, 0);
			else if (rd[i + 1] == '\t')
				put_var_end(h, 0, NULL, 0);
			else if (rd[i + 1] == ';')
				put_var_end(h, 0, NULL, 0);
			else
				check_env(h, rd + i, data);
		}
	}

	return (i);
}

/**
 * replaced_input - replaces string into variables
 * @head: head of the linked list
 * @read: read string
 * @new_read: new read string
 * @nlen: new length
 * Return: replaced string
 */
char *replaced_input(var_ls **head, char *read, char *new_read, int nlen)
{
	var_ls *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (read[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_vl))
			{
				new_read[i] = read[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_vl))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_vl; k++)
				{
					new_read[i] = indx->vl[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_read[i] = read[j];
			j++;
		}
	}

	return (new_read);
}

/**
 * rep_var - calls functions to replace string into vars
 * @read: read string
 * @datash: data structure
 * Return: replaced string
 */
char *rep_var(char *read, data_sh *datash)
{
	var_ls *head, *indx;
	char *status, *new_read;
	int olen, nlen;

	status = _itoa(datash->status);
	head = NULL;

	olen = check_var(&head, read, status, datash);

	if (head == NULL)
	{
		free(status);
		return (read);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_vl - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_read = malloc(sizeof(char) * (nlen + 1));
	new_read[nlen] = '\0';

	new_read = replaced_input(&head, read, new_read, nlen);

	free(read);
	free(status);
	free_var_list(&head);

	return (new_read);
}
