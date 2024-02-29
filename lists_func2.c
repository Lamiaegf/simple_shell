#include "main.h"

/**
 * put_var_end - adds a variable at the end
 * of a var_ls.
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @var: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */
var_ls *put_var_end(var_ls **head, int lvar, char *var, int lval)
{
	var_ls *new, *tmp;

	new = malloc(sizeof(var_ls));
	if (new == NULL)
		return (NULL);

	new->len_var = lvar;
	new->vl = var;
	new->len_vl = lval;

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
 * free_var_list - deallocate a var_ls.
 * @head: head of the linked list.
 * Return: nothing
 */
void free_var_list(var_ls **head)
{
	var_ls *tmp;
	var_ls *current;

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
