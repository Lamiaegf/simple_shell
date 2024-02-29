#include "main.h"

/**
 * set_env - sets an environment variable
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure (environ)
 * Return: no return
 */
void set_env(char *name, char *value, data_sh *datash)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; datash->_env[i]; i++)
	{
		var_env = _strdup(datash->_env[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_env[i]);
			datash->_env[i] = copy_data(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datash->_env = realloc_dp(datash->_env, i, sizeof(char *) * (i + 2));
	datash->_env[i] = copy_data(name, value);
	datash->_env[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names with the name passed.
 * @datash: data relevant (env name and env value)
 * Return: 1 on success.
 */
int _setenv(data_sh *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 * @datash: data relevant (env name)
 * Return: 1 on success.
 */
int _unsetenv(data_sh *datash)
{
	char **realloc_env;
	char *var_env, *name_env;
	int i, j, k;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datash->_env[i]; i++)
	{
		var_env = _strdup(datash->_env[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datash->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_env = malloc(sizeof(char *) * (i));
	for (i = j = 0; datash->_env[i]; i++)
	{
		if (i != k)
		{
			realloc_env[j] = datash->_env[i];
			j++;
		}
	}
	realloc_env[j] = NULL;
	free(datash->_env[k]);
	free(datash->_env);
	datash->_env = realloc_env;
	return (1);
}
