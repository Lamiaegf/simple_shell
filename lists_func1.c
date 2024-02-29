#include "main.h"

/**
 * put_line_end - adds a command line at the end
 * of a line_ls.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
line_ls *put_line_end(line_ls **head, char *line)
{
	line_ls *new, *tmp;

	new = malloc(sizeof(line_ls));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	tmp = *head;

	if (tmp == NULL)
	{
		*head = new;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}

	return (*head);
}

/**
 * free_line_list - deallocate a line_list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_line_list(line_ls **head)
{
	line_ls *tmp;
	line_ls *current;

	if (head != NULL)
	{
		current = *head;
		while ((tmp = current) != NULL)
		{
			current = current->next;
			free(tmp);
		}
		*head = NULL;
	}
}

/**
 * put_spt_end - adds a separator at the end of a spt_ls.
 * @head: head of the linked list.
 * @spt: separator found (; | &).
 * Return: address of the head.
 */
spt_ls *put_spt_end(spt_ls **head, char spt)
{
	spt_ls *new, *tmp;

	new = malloc(sizeof(spt_ls));
	if (new == NULL)
		return (NULL);

	new->sept = spt;
	new->next = NULL;
	tmp = *head;

	if (tmp == NULL)
	{
		*head = new;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}

	return (*head);
}

/**
 * free_spt_list - frees a spt_ls
 * @head: head of the linked list.
 * Return: no return.
 */
void free_spt_list(spt_ls **head)
{
	spt_ls *tmp;
	spt_ls *current;

	if (head != NULL)
	{
		current = *head;
		while ((tmp = current) != NULL)
		{
			current = current->next;
			free(tmp);
		}
		*head = NULL;
	}
}
