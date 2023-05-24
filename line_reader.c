#include "main.h"

/**
 * line_reader - function to reads the input string.
 *
 * @reader: return value of getline function
 * Return: input string
 */
char *line_reader(int *reader)
{
	char *c = NULL;
	size_t buffs = 0;

	*reader = getline(&c, &buffs, stdin);

	return (c);
}

