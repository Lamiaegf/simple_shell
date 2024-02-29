#include "main.h"

/**
 * cmp_env_name - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_env: environment variable
 * Return: value of the environment variable if is found.
 * else, returns NULL.
 */
char *_getenv(const char *name, char **_env)
{
	char *ptr_env;
	int i, mov;

	ptr_env = NULL;
	mov = 0;
	for (i = 0; _env[i]; i++)
	{
		mov = cmp_env_name(_env[i], name);
		if (mov)
		{
			ptr_env = _env[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - print the evironment variables
 * @datash: data relevant.
 * Return: 1 on success.
 */
int _env(data_sh *datash)
{
	int i, j;

	for (i = 0; datash->_env[i]; i++)
	{

		for (j = 0; datash->_env[i][j]; j++)
			;

		write(STDOUT_FILENO, datash->_env[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}

/**
 * copy_data - copies info to create a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 * Return: new env or alias.
 */
char *copy_data(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

