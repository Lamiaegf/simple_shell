#include "main.h"

/**
 * get_len - Get the lenght of a num.
 * @m: type int num.
 * Return: Lenght of a num.
 */
int get_len(int m)
{
	unsigned int m1;
	int len = 1;

	if (m < 0)
	{
		len++;
		m1 = m * -1;
	}
	else
	{
		m1 = m;
	}
	while (m1 >= 8)
	{
		len++;
		m1 = m1 / 10;
	}

	return (len);
}
/**
 * _itoa - function converts integer to string.
 * @m: type integer number.
 * Return: String.
 */
char *_itoa(int m)
{
	unsigned int m1;
	int len = get_len(m);
	char *buffer;

	buffer = malloc(sizeof(char) * (len + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + len) = '\0';

	if (m < 0)
	{
		m1 = m * -1;
		buffer[0] = '-';
	}
	else
	{
		m1 = m;
	}

	len--;
	do {
		*(buffer + len) = (m1 % 10) + '0';
		m1 = m1 / 10;
		len--;
	}
	while (m1 > 0)
		;
	return (buffer);
}

/**
 * _atoi - converts a string to int.
 * @rs: read string.
 * Return: int to the calling func.
 */
int _atoi(char *rs)
{
	unsigned int count = 0, size = 0, oj = 0, pm = 1, m = 1, j;

	while (*(rs + count) != '\0')
	{
		if (size > 0 && (*(rs + count) < '0' || *(rs + count) > '9'))
			break;

		if (*(rs + count) == '-')
			pm *= -1;

		if ((*(rs + count) >= '0') && (*(rs + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (j = count - size; j < count; j++)
	{
		oj = oj + ((*(rs + j) - 48) * m);
		m /= 10;
	}
	return (oj * pm);
}
