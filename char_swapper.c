#include "main.h"

/**
 * char_swapper - function to swap and , or operators
 *
 * @src: src string
 * @swap_type: swap type
 * Return: swapped string
 */
char *char_swapper(char *src, int swap_type)
{
	int i;

	if (swap_type == 0)
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
 * add_nodes - function to add comand line and separators in list
 *
 * @head_s: the head of separator list
 * @head_l: the head of command lines list
 * @src_str: src_str string
 * Return: no return
 */
void add_nodes(sepo_list **head_s, line_list **head_l, char *src_str)
{
	int i;
	char *line;

	src_str = char_swapper(src_str, 0);

	for (i = 0; src_str[i]; i++)
	{
		if (src_str[i] == ';')
			add_sepo_node_end(head_s, src_str[i]);

		if (src_str[i] == '|' || src_str[i] == '&')
		{
			add_sepo_node_end(head_s, src_str[i]);
			i++;
		}
	}

	line = _strtoko(src_str, ";|&");
	do {
		line = char_swapper(line, 1);
		add_line_node_end(head_l, line);
		line = _strtoko(NULL, ";|&");
	} while (line != NULL);

}

/**
 * go_next - function to go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @shell_data: data structure
 * Return: no return
 */
void go_next(sepo_list **list_s, line_list **list_l, shelldata_t *shell_data)
{
	int loop_sep;
	sepo_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (shell_data->status == 0)
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
 * split_commands - function to splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @shell_data: data structure
 * @src: src string
 * Return: 0 to exit, 1 to continue
 */
int split_commands(shelldata_t *shell_data, char *src)
{

	sepo_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, src);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		shell_data->input = list_l->line;
		shell_data->args = split_line(shell_data->input);
		loop = line_executor(shell_data);
		free(shell_data->args);

		if (loop == 0)
			break;

		go_next(&list_s, &list_l, shell_data);

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
 * split_line - function to tokenizes the src string
 *
 * @src: src string.
 * Return: string splitted.
 */
char **split_line(char *src)
{
	size_t buff_size;
	size_t i;
	char **tokens;
	char *token;

	buff_size = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (buff_size));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtoko(src, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == buff_size)
		{
			buff_size += TOK_BUFSIZE;
			tokens = _reallocdpo(tokens, i, sizeof(char *) * buff_size);
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
