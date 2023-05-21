#include "main.h"

/**
 * char_repeat - counts the repetitions of a char
 *
 * @inp: input string
 * @i: index
 * Return: repetitions
 */
int char_repeat(char *inp, int i)
{
	if (*(inp - 1) == *inp)
		return (char_repeat(inp - 1, i + 1));

	return (i);
}

/**
 * sep_errors - finds syntax errors
 *
 * @inp: inp string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int sep_errors(char *inp, int i, char last)
{
	int count;

	count = 0;
	if (*inp == '\0')
		return (0);

	if (*inp == ' ' || *inp == '\t')
		return (sep_errors(inp + 1, i + 1, last));

	if (*inp == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*inp == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = char_repeat(inp, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*inp == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = char_repeat(inp, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (sep_errors(inp + 1, i + 1, *inp));
}

/**
 * check_first - finds index of the first char
 *
 * @src: src string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int check_first(char *src, int *i)
{

	for (*i = 0; src[*i]; *i += 1)
	{
		if (src[*i] == ' ' || src[*i] == '\t')
			continue;

		if (src[*i] == ';' || src[*i] == '|' || src[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * error_print_syntax - prints when a syntax error is found
 *
 * @datash: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void error_print_syntax(shelldata_t *datash, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = utils_itoa(datash->counter);
	length = _strleno(datash->av[0]) + _strleno(counter);
	length += _strleno(msg) + _strleno(msg2) + _strleno(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpyo(error, datash->av[0]);
	_strcato(error, ": ");
	_strcato(error, counter);
	_strcato(error, msg2);
	_strcato(error, msg);
	_strcato(error, msg3);
	_strcato(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * error_check_syntax - intermediate function to
 * find and print a syntax error
 *
 * @datash: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int error_check_syntax(shelldata_t *datash, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = check_first(input, &begin);
	if (f_char == -1)
	{
		error_print_syntax(datash, input, begin, 0);
		return (1);
	}

	i = sep_errors(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		error_print_syntax(datash, input, begin + i, 1);
		return (1);
	}

	return (0);
}

