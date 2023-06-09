#include "main.h"

/**
 * line_executor - search line for comands
 *
 * @shelldata: data (args)
 * Return: 1 on success.
 */
int line_executor(shelldata_t *shelldata)
{
	int (*builtin)(shelldata_t *shelldata);

	if (shelldata->args[0] == NULL)
		return (1);

	builtin = get_builtin(shelldata->args[0]);

	if (builtin != NULL)
		return (builtin(shelldata));

	return (exec_command(shelldata));
}

