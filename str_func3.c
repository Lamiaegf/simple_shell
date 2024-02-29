#include "main.h"

/**
 * _isdigit - checks if the passed string is a number
 *
 * @s: string passed
 * Return: 1 if string is a number otherwise 0.
 */
int _isdigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}

/**
 * cmp_chars - compare characters of strings
 * @s: input string.
 * @d: delimiter.
 *
 * Return: 1 if are equals, otherwise 0.
 */
int cmp_chars(char s[], const char *d)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; s[i]; i++)
	{
		for (j = 0; d[j]; j++)
		{
			if (s[i] == d[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _strtok - split a string in multiple strings by some delimiter.
 * @s: input string.
 * @d: delimiter.
 *
 * Return: string splited.
 */
char *_strtok(char s[], const char *d)
{
	static char *splt, *s_tail;
	char *s_begin;
	unsigned int i, bool;

	if (s != NULL)
	{
		if (cmp_chars(s, d))
			return (NULL);
		splt = s;
		i = _strlen(s);
		s_tail = &s[i];
	}
	s_begin = splt;
	if (s_begin == s_tail)
		return (NULL);

	for (bool = 0; *splt; splt++)
	{
		if (splt != s_begin)
			if (*splt && *(splt - 1) == '\0')
				break;

		for (i = 0; d[i]; i++)
		{
			if (*splt == d[i])
			{
				*splt = '\0';
				if (splt == s_begin)
					s_begin++;
				break;
			}
		}
		if (bool == 0 && *splt)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (s_begin);
}

