#include "main.h"

/**
 * comment_remover - function to delete # deletes comments from the input
 *
 * @src: input string
 * Return: input without comments
 */
char *comment_remover(char *src)
{
	int i, length;

	length = 0;
	for (i = 0; src[i]; i++)
	{
		if (src[i] == '#')
		{
			if (i == 0)
			{
				free(src);
				return (NULL);
			}

			if (src[i - 1] == ' ' || src[i - 1] == '\t' || src[i - 1] == ';')
				length = i;
		}
	}

	if (length != 0)
	{
		src = _realloco(src, i, length + 1);
		src[length] = '\0';
	}

	return (src);
}

/**
 * shell_looper - the main Loop of shell
 * @shelldata: data relevant (av, input, args)
 *
 * Return: no return.
 */
void shell_looper(shelldata_t *shelldata)
{
	int check_loop, n;
	char *input;

	check_loop = 1;
	while (check_loop == 1)
	{
		write(STDIN_FILENO, "shelly$ ", 8);
		input = line_reader(&n);
		if (n != -1)
		{
			input = comment_remover(input);
			if (input == NULL)
				continue;

			if (error_check_syntax(shelldata, input) == 1)
			{
				shelldata->status = 2;
				free(input);
				continue;
			}
			input = vars_replace(input, shelldata);
			check_loop = split_commands(shelldata, input);
			shelldata->counter += 1;
			free(input);
		}
		else
		{
			check_loop = 0;
			free(input);
		}
	}
}

