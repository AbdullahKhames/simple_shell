#include "main.h"

/**
 * comment_remover - deletes comments from the input
 *
 * @c: input string
 * Return: input without comments
 */
char *comment_remover(char *c)
{
	int i, len;

	len = 0;
	for (i = 0; c[i]; i++)
	{
		if (c[i] == '#')
		{
			if (i == 0)
			{
				free(c);
				return (NULL);
			}

			if (c[i - 1] == ' ' || c[i - 1] == '\t' || c[i - 1] == ';')
				len = i;
		}
	}

	if (len != 0)
	{
		c = _realloco(c, i, len + 1);
		c[len] = '\0';
	}

	return (c);
}

/**
 * shell_looper - Loop of shell
 * @datash: data relevant (av, input, args)
 *
 * Return: no return.
 */
void shell_looper(shelldata_t *datash)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "shelly$ ", 8);
		input = line_reader(&i_eof);
		if (i_eof != -1)
		{
			input = comment_remover(input);
			if (input == NULL)
				continue;

			if (error_check_syntax(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = vars_replace(input, datash);
			loop = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
