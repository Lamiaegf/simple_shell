#include "main.h"

/**
 * first_char - finds index of the first char
 * @read: input string
 * @i: index
 * Return: -1 if there is an error,otherwise 0.
 */
int first_char(char *read, int *i)
{

	for (*i = 0; read[*i]; *i += 1)
	{
		if (read[*i] == ' ' || read[*i] == '\t')
			continue;

		if (read[*i] == ';' || read[*i] == '|' || read[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * repeated_char - counts the repetitions of a character
 * @read: input string
 * @i: index
 * Return: Repetitions
 */
int repeated_char(char *read, int i)
{
	if (*(read - 1) == *read)
		return (repeated_char(read - 1, i + 1));

	return (i);
}

/**
 * error_spt_op - finds syntax errors
 * @read: input string
 * @i: index
 * @last: last character to read
 * Return: index of error. 0 when there are no errors
 */
int error_spt_op(char *read, int i, char last)
{
	int count;

	count = 0;
	if (*read == '\0')
		return (0);

	if (*read == ' ' || *read == '\t')
		return (error_spt_op(read + 1, i + 1, last));

	if (*read == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*read == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = repeated_char(read, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*read == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = repeated_char(read, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (error_spt_op(read + 1, i + 1, *read));
}

/**
 * display_syntax_error - prints when a syntax error is found
 * @datash: data structure
 * @read: input string
 * @i: index of the error
 * @bool: to control msg error
 * Return: nothing
 */
void display_syntax_error(data_sh *datash, char *read, int i, int bool)
{
	char *msg1, *msg2, *msg3, *error, *counter;
	int len;

	if (read[i] == ';')
	{
		if (bool == 0)
			msg1 = (read[i + 1] == ';' ? ";;" : ";");
		else
			msg1 = (read[i - 1] == ';' ? ";;" : ";");
	}

	if (read[i] == '|')
		msg1 = (read[i + 1] == '|' ? "||" : "|");

	if (read[i] == '&')
		msg1 = (read[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = _itoa(datash->counter);
	len = _strlen(datash->argv[0]) + _strlen(counter);
	len += _strlen(msg1) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, datash->argv[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg1);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, len);
	free(error);
	free(counter);
}

/**
 * check_syntax_error - function to find and print a syntax error
 * @datash: data structure
 * @read: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_error(data_sh *datash, char *read)
{
	int start = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_char(read, &start);
	if (f_char == -1)
	{
		display_syntax_error(datash, read, start, 0);
		return (1);
	}

	i = error_spt_op(read + start, 0, *(read + start));
	if (i != 0)
	{
		display_syntax_error(datash, read, start + i, 1);
		return (1);
	}

	return (0);
}
