#include "main.h"

/**
 * strcat_cd - function that concatenates the message for cd error
 *
 * @datash: data relevant (directory)
 * @msg: message to print
 * @error: output message
 * @count_l: counter lines
 * Return: error message
 */
char *strcat_cd(data_sh *datash, char *msg, char *error, char *count_l)
{
	char *illegal_f;

	_strcpy(error, datash->argv[0]);
	_strcat(error, ": ");
	_strcat(error, count_l);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, msg);
	if (datash->args[1][0] == '-')
	{
		illegal_f = malloc(3);
		illegal_f[0] = '-';
		illegal_f[1] = datash->args[1][1];
		illegal_f[2] = '\0';
		_strcat(error, illegal_f);
		free(illegal_f);
	}
	else
	{
		_strcat(error, datash->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_cd - error message for cd command
 * @datash: data relevant (directory)
 * Return: Error message
 */
char *error_cd(data_sh *datash)
{
	int len, len_id;
	char *error, *count_l, *msg;

	count_l = _itoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(datash->args[1]);
	}

	len = _strlen(datash->argv[0]) + _strlen(datash->args[0]);
	len += _strlen(count_l) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (len + 1));

	if (error == 0)
	{
		free(count_l);
		return (NULL);
	}

	error = strcat_cd(datash, msg, error, count_l);

	free(count_l);

	return (error);
}

/**
 * error_not_found - error message for command not found
 * @datash: data relevant (counter, arguments)
 * Return: Error message
 */
char *error_not_found(data_sh *datash)
{
	int len;
	char *error;
	char *count_l;

	count_l = _itoa(datash->counter);
	len = _strlen(datash->argv[0]) + _strlen(count_l);
	len += _strlen(datash->args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(error);
		free(count_l);
		return (NULL);
	}
	_strcpy(error, datash->argv[0]);
	_strcat(error, ": ");
	_strcat(error, count_l);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(count_l);
	return (error);
}

/**
 * error_exit_shell - error message for exit in get_exit
 * @datash: data relevant (counter, arguments)
 * Return: Error message
 */
char *error_exit_shell(data_sh *datash)
{
	int len;
	char *error;
	char *count_l;

	count_l = _itoa(datash->counter);
	len = _strlen(datash->argv[0]) + _strlen(count_l);
	len += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(count_l);
		return (NULL);
	}
	_strcpy(error, datash->argv[0]);
	_strcat(error, ": ");
	_strcat(error, count_l);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, datash->args[1]);
	_strcat(error, "\n\0");
	free(count_l);

	return (error);
}
