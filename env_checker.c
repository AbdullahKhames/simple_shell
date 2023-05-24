#include "main.h"

/**
 * env_checker - checks for variable if present in current environment
 *
 * @h: head of linked list
 * @input: input string
 * @ahelldata: data structure
 * Return: no return
 */
void env_checker(r_varo **h, char *input, shelldata_t *shelldata)
{
	int row, chr, j, lval;
	char **_environment;

	_environment = shelldata->_environ;
	for (row = 0; _environment[row]; row++)
	{
		for (j = 1, chr = 0; _environment[row][chr]; chr++)
		{
			if (_environment[row][chr] == '=')
			{
				lval = _strleno(_environment[row] + chr + 1);
				add_rvaro_node(h, j, _environment[row] + chr + 1, lval);
				return;
			}

			if (input[j] == _environment[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; input[j]; j++)
	{
		if (input[j] == ';' || input[j] == '\n' || input[j] == ' ' || input[j] == '\t')
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
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *input_replace(r_varo **head, char *input, char *new_input, int nlen)
{
	r_varo *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < nlen; i++)
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
 * @datash: data structure
 * Return: replaced string
 */
char *vars_replace(char *input, shelldata_t *datash)
{
	r_varo *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = utils_itoa(datash->status);
	head = NULL;

	olen = vars_checker(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = input_replace(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvaro_list(&head);

	return (new_input);
}

