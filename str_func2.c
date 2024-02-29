#include "main.h"

/**
 * _strspn - gets the length of a prefix substring
 * @s: pointer to string
 * @receive: character
 * Return: length
 */

int _strspn(char *s, char *receive)
{
	int i, j;
	unsigned int count = 0;

	for (i = 0; (s[i] != ' ' && s[i] != '\0'); i++)
	{
		for (j = 0; receive[j] != '\0'; j++)
		{
			if (s[i] == receive[j])
			{
				count++;
			}
		}
	}
	return (count);
}

/**
 * _strlen - return the length of a string
 * @s: the string to get the length of
 * Return: the length of string s
 */
int _strlen(const char *s)
{
	int len = 0;

	while (*s++)
	{
		len++;
	}
	return (len);
}

/**
 * rev_string - reverses a string
 * @s: string reversed
 * Return: void
 */
void rev_string(char *s)
{
	int len = 0, i = 0;
	char c;

	while (s[i++])
	{
		len++;
	}
	for (i = len - 1; i >= len / 2; i--)
	{
		c = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = c;
	}
}

/**
 * _strdup - duplicate a string pointed to by s
 * @s: pointer to a string
 *
 * Return: pointer to a string
 */
char *_strdup(const char *s)
{
	int i, len;
	char *new;

	if (s == NULL)
	{
		return (NULL);
	}
	for (len = 0; s[len] != '\0'; len++)
	{
	}
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
	{
		return (NULL);
	}
	for (i = 0; i <= len; i++)
	{
		new[i] = s[i];
	}
	return (new);
}
