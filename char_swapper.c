#include "main.h"

/**
 * char_swapper - swaps | and & for non-printed chars
 *
 * @src: src string
 * @bool: type of swap
 * Return: swapped string
 */
char *char_swapper(char *src, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; src[i]; i++)
		{
			if (src[i] == '|')
			{
				if (src[i + 1] != '|')
					src[i] = 16;
				else
					i++;
			}

			if (src[i] == '&')
			{
				if (src[i + 1] != '&')
					src[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; src[i]; i++)
		{
			src[i] = (src[i] == 16 ? '|' : src[i]);
			src[i] = (src[i] == 12 ? '&' : src[i]);
		}
	}
	return (src);
}

/**
 * add_nodes - add separators and command lines in the lists
 *
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @input: input string
 * Return: no return
 */
void add_nodes(sepo_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *line;

	input = char_swapper(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_sepo_node_end(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_sepo_node_end(head_s, input[i]);
			i++;
		}
	}

	line = _strtoko(input, ";|&");
	do {
		line = char_swapper(line, 1);
		add_line_node_end(head_l, line);
		line = _strtoko(NULL, ";|&");
	} while (line != NULL);

}

/**
 * go_next - go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @datash: data structure
 * Return: no return
 */
void go_next(sepo_list **list_s, line_list **list_l, shelldata_t *datash)
{
	int loop_sep;
	sepo_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @datash: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int split_commands(shelldata_t *datash, char *input)
{

	sepo_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = split_line(datash->input);
		loop = line_executor(datash);
		free(datash->args);

		if (loop == 0)
			break;

		go_next(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sepo_list(&head_s);
	free_line_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - tokenizes the input string
 *
 * @input: input string.
 * Return: string splitted.
 */
char **split_line(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtoko(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocdpo(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtoko(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}

