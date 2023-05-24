#include "main.h"

/**
 * shell_exiter - builtin comand to exit the shell
 *
 * @shelldata: data (status and args)
 * Return: 0 on success.
 */
int shell_exiter(shelldata_t *shelldata)
{
	unsigned int ustatus;
	int is_digit;
	int len;
	int num;

	if (shelldata->args[1] != NULL)
	{
		ustatus = _atoio(shelldata->args[1]);
		is_digit = _isdigito(shelldata->args[1]);
		len = _strleno(shelldata->args[1]);
		num = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || len > 10 || num)
		{
			error_getter(shelldata, 2);
			shelldata->status = 2;
			return (1);
		}
		shelldata->status = (ustatus % 256);
	}
	return (0);
}

