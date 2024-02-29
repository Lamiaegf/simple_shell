#include "main.h"

/**
 * cd_dot - it changes to the parent directory
 * @datash: for data pertinent (env)
 * Return: nothing
 */
void cd_dot(data_sh *datash)
{
	char pwd[PATH_MAX];
	char *dirr, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, datash);
	dirr = datash->args[1];
	if (_strcmp(".", dirr) == 0)
	{
		set_env("PWD", cp_pwd, datash);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, datash);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datash);
	}
	datash->status = 0;
	free(cp_pwd);
}

/**
 * cd_to - changes to a directory given
 * by the user
 * @datash: data relevant (directories)
 * Return: no return
 */
void cd_to(data_sh *datash)
{
	char pwd[PATH_MAX];
	char *dirr, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dirr = datash->args[1];
	if (chdir(dirr) == -1)
	{
		get_error(datash, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, datash);

	cp_dir = _strdup(dirr);
	set_env("PWD", cp_dir, datash);

	free(cp_pwd);
	free(cp_dir);

	datash->status = 0;

	chdir(dirr);
}

/**
 * cd_back - changes to the previous directory
 * @datash: data relevant (env)
 * Return: no return
 */
void cd_back(data_sh *datash)
{
	char pwd[PATH_MAX];
	char *f_pwd, *f_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	f_oldpwd = _getenv("OLDPWD", datash->_env);

	if (f_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(f_oldpwd);

	set_env("OLDPWD", cp_pwd, datash);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, datash);
	else
		set_env("PWD", cp_oldpwd, datash);

	f_pwd = _getenv("PWD", datash->_env);

	write(STDOUT_FILENO, f_pwd, _strlen(f_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (f_oldpwd)
		free(cp_oldpwd);

	datash->status = 0;

	chdir(f_pwd);
}

/**
 * cd_home - changes to home directory
 *
 * @datash: data relevant (env)
 * Return: no return
 */
void cd_home(data_sh *datash)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", datash->_env);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, datash);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(datash, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, datash);
	set_env("PWD", home, datash);
	free(p_pwd);
	datash->status = 0;
}

/**
 * cd_sh - changes current directory
 * @datash: data relevant
 * Return: 1 on success
 */
int cd_sh(data_sh *datash)
{
	int ishome, ishome2, isddash;
	char *dirr;

	dirr = datash->args[1];

	if (dirr != NULL)
	{
		ishome = _strcmp("$HOME", dirr);
		ishome2 = _strcmp("~", dirr);
		isddash = _strcmp("--", dirr);
	}

	if (dirr == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_home(datash);
		return (1);
	}

	if (_strcmp("-", dirr) == 0)
	{
		cd_back(datash);
		return (1);
	}

	if (_strcmp(".", dirr) == 0 || _strcmp("..", dirr) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	cd_to(datash);

	return (1);
}
