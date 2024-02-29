#include "main.h"

/**
 * error_env - error message for env in get_env.
 * @datash: data relevant
 * Return: error message.
 */
char *error_env(data_sh *datash)
{
	int len;
	char *error;
	char *count_l;
	char *msg;

	count_l = _itoa(datash->counter);
	msg = ": Unable to add/remove from environment\n";
	len = _strlen(datash->argv[0]) + _strlen(count_l);
	len += _strlen(datash->args[0]) + _strlen(msg) + 4;
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
	_strcat(error, msg);
	_strcat(error, "\0");
	free(count_l);

	return (error);
}

/**
 * error_path - error message for path and failure denied permission.
 * @datash: data relevant (counter, arguments)
 * Return: The error string.
 */
char *error_path(data_sh *datash)
{
	int len;
	char *count_l;
	char *error;

	count_l = _itoa(datash->counter);
	len = _strlen(datash->argv[0]) + _strlen(count_l);
	len += _strlen(datash->args[0]) + 24;
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
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(count_l);
	return (error);
}
