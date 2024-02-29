#include "main.h"

/**
 * get_error - calls the error according the builtin, syntax or permission
 * @datash: data structure
 * @eval: error value
 * Return: error
 */
int get_error(data_sh *datash, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = error_env(datash);
		break;
	case 126:
		error = error_path(datash);
		break;
	case 127:
		error = error_not_found(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			error = error_exit_shell(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			error = error_cd(datash);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	datash->status = eval;
	return (eval);
}

/**
 * get_sigint - Handle the crtl + c call in prompt
 * @sig: Signal handler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$$ ", 5);
}

/**
 * get_help - function that get back  help messages according builtin
 * @datash: data structure (args and input)
 * Return: Return 0
*/
int get_help(data_sh *datash)
{

	if (datash->args[1] == 0)
		help_general();
	else if (_strcmp(datash->args[1], "setenv") == 0)
		help_setenv();
	else if (_strcmp(datash->args[1], "env") == 0)
		help_env();
	else if (_strcmp(datash->args[1], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(datash->args[1], "help") == 0)
		help();
	else if (_strcmp(datash->args[1], "exit") == 0)
		help_exit();
	else if (_strcmp(datash->args[1], "cd") == 0)
		help_cd();
	else if (_strcmp(datash->args[1], "alias") == 0)
		help_alias();
	else
		write(STDERR_FILENO, datash->args[0],
		      _strlen(datash->args[0]));

	datash->status = 0;
	return (1);
}

/**
 * get_builtin - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(data_sh *)
{
	builtin_s builtin[] = {
		{ "env", _env },
		{ "exit", exit_sh },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_sh },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}
