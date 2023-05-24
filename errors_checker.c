#include "main.h"

/**
 * char_repeat - function to count the repetitions of a char
 *
 * @input: inputut string
 * @i: index
 * Return: repetitions
 */
int char_repeat(char *input, int i)
{
	if (*(input - 1) == *input)
		return (char_repeat(input - 1, i + 1));

	return (i);
}

/**
 * sep_errors - function to finds syntax errors
 *
 * @input: input string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int sep_errors(char *input, int i, char last)
{
	int counter;

	counter = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (sep_errors(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			counter = char_repeat(input, 0);
			if (counter == 0 || counter > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			counter = char_repeat(input, 0);
			if (counter == 0 || counter > 1)
				return (i);
		}
	}

	return (sep_errors(input + 1, i + 1, *input));
}

/**
 * check_first - function to finds index of the first char
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
 * error_print_syntax - function to prints when a syntax error is found
 *
 * @shelldata: data structure
 * @input: input string
 * @i: index of the error
 * @msg_bo: to control msg error
 * Return: no return
 */
void error_print_syntax(shelldata_t *shelldata, char *input, int i, int msg_bo)
{
	char *msg, *syntax_error, *full_message, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (msg_bo == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	syntax_error = ": Syntax error: \"";
	full_message = "\" unexpected\n";
	counter = utils_itoa(shelldata->counter);
	length = _strleno(shelldata->av[0]) + _strleno(counter);
	length += _strleno(msg) + _strleno(syntax_error) + _strleno(full_message) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpyo(error, shelldata->av[0]);
	_strcato(error, ": ");
	_strcato(error, counter);
	_strcato(error, syntax_error);
	_strcato(error, msg);
	_strcato(error, full_message);
	_strcato(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * error_check_syntax - function to find intermediate function to
 * find and print a syntax error
 *
 * @shelldata: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int error_check_syntax(shelldata_t *shelldata, char *input)
{
	int first = 0;
	int first_char = 0;
	int i = 0;

	first_char = check_first(input, &first);
	if (first_char == -1)
	{
		error_print_syntax(shelldata, input, first, 0);
		return (1);
	}

	i = sep_errors(input + first, 0, *(input + first));
	if (i != 0)
	{
		error_print_syntax(shelldata, input, first + i, 1);
		return (1);
	}

	return (0);
}
