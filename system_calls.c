#include "main.h"

/**
 * read_line - reads the input string.
 * @edf: return value of getline function.
 * Return: input string
 */
char *read_line(int *edf)
{
	char *read = NULL;
	size_t bufsize = 0;

	*edf = getline(&read, &bufsize, stdin);

	return (read);
}

/**
 * show_line - assigns the line var for get_line
 * @linef: Buffer that store the input str
 * @buffer: str that is been called to line
 * @m: size of line
 * @k: size of buffer
 */
void show_line(char **linef, size_t *m, char *buffer, size_t k)
{

	if (*linef == NULL)
	{
		if  (k > BUFSIZE)
			*m = k;

		else
			*m = BUFSIZE;
		*linef = buffer;
	}
	else if (*m < k)
	{
		if (k > BUFSIZE)
			*m = k;
		else
			*m = BUFSIZE;
		*linef = buffer;
	}
	else
	{
		_strcpy(*linef, buffer);
		free(buffer);
	}
}
/**
 * get_line - Read inpt from stream
 * @linef: buffer that stores the input
 * @m: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t get_line(char **linef, size_t *m, FILE *stream)
{
	int j;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char u = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (u != '\n')
	{
		j = read(STDIN_FILENO, &u, 1);
		if (j == -1 || (j == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (j == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = u;
		input++;
	}
	buffer[input] = '\0';
	show_line(linef, m, buffer, input);
	retval = input;
	if (j != 0)
		input = 0;
	return (retval);
}

/**
 * exec_line - finds builtins and commands
 * @datash: data relevant (args)
 * Return: 1 on success.
 */
int exec_line(data_sh *datash)
{
	int (*builtin)(data_sh *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = get_builtin(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (cmd_exec(datash));
}
