#include "main.h"

/**
 * line_reader - reads the input string.
 *
 * @read: return value of getline function
 * Return: input string
 */
char *line_reader(int *read)
{
	char *input = NULL;
	size_t bufsize = 0;

	*read = getline(&input, &bufsize, stdin);

	return (input);
}

