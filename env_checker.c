#include "main.h"

/**
 * env_checker - checks for variable if present in current environment
 *
 * @h: head of linked list
 * @input: input string
 * @shelldata: data structure
 * Return: no return
 */
void env_checker(r_varo **h, char *input, shelldata_t *shelldata)
{
	int row, sh_char, j, val_l;
	char **_environment;

	_environment = shelldata->_environ;
	for (row = 0; _environment[row]; row++)
	{
		for (j = 1, sh_char = 0; _environment[row][sh_char]; sh_char++)
		{
			if (_environment[row][sh_char] == '=')
			{
				val_l = _strleno(_environment[row] + sh_char + 1);
				add_rvaro_node(h, j, _environment[row] + sh_char + 1, val_l);
				return;
			}

			if (input[j] == _environment[row][sh_char])
				j++;
			else
				break;
		}
	}

	for (j = 0; input[j]; j++)
	{
		if (input[j] == ';' || input[j] == '\n')
			break;
		else if (input[j] == ' ' || input[j] == '\t')
			break;
	}

	add_rvaro_node(h, j, NULL, 0);
}

/**
 * vars_checker - check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int vars_checker(r_varo **h, char *in, char *st, shelldata_t *data)
{
	int i, lst, lpd;

	lst = _strleno(st);
	lpd = _strleno(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_rvaro_node(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				add_rvaro_node(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_rvaro_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_rvaro_node(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_rvaro_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_rvaro_node(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_rvaro_node(h, 0, NULL, 0);
			else
				env_checker(h, in + i, data);
		}
	}

	return (i);
}
/**
 * input_replace - replaces string into variables
 *
 * @head: head of the linked list
 * @input: input string
 * @new_input: string to be replaced
 * new input string (replaced)
 * @new_leng: new length
 * Return: replaced string
 */
char *input_replace(r_varo **head, char *input, char *new_input, int new_leng)
{
	r_varo *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < new_leng; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * vars_replace - calls functions to replace string into vars
 *
 * @input: input string
 * @shelldata: data structure
 * Return: replaced string
 */
char *vars_replace(char *input, shelldata_t *shelldata)
{
	r_varo *head, *indx;
	char *status, *new_input;
	int olen, new_length;

	status = utils_itoa(shelldata->status);
	head = NULL;

	olen = vars_checker(&head, input, status, shelldata);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	new_length = 0;

	while (indx != NULL)
	{
		new_length += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	new_length += olen;

	new_input = malloc(sizeof(char) * (new_length + 1));
	new_input[new_length] = '\0';

	new_input = input_replace(&head, input, new_input, new_length);

	free(input);
	free(status);
	free_rvaro_list(&head);

	return (new_input);
}
