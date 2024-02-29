#include "main.h"

/**
 * _memcpy - copy a block of memory between void pointers.
 * @dest: destination pointer.
 * @src: source pointer.
 * @size: size of the new pointer.
 * Return: no return.
 */
void _memcpy(void *dest, const void *src, unsigned int size)
{
	char *s_rc = (char *)src;
	char *d_est = (char *)dest;
	unsigned int i;

	for (i = 0; i < size; i++)
		d_est[i] = s_rc[i];
}

/**
 * _realloc - reallocates a given area of memrory.
 * @p: pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of p.
 * @new_size: new size,of the new memory block.
 *
 * Return: pointer (p).
 * if new_size equal to old_size, returns p without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc(void *p, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (p == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(p);
		return (NULL);
	}

	if (new_size == old_size)
		return (p);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newptr, p, new_size);
	else
		_memcpy(newptr, p, old_size);

	free(p);
	return (newptr);
}

/**
 * realloc_dp - reallocates a memory block of a double pointer.
 * @p: double pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of p.
 * @new_size: new size of the new memory block.
 *
 * Return: p.
 * if new_size == old_size, returns p without changes.
 * otherwise returns NULL(malloc fails).
 */
char **realloc_dp(char **p, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (p == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (p);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = p[i];

	free(p);

	return (newptr);
}
