#include "main.h"

/**
 * shell_exiter - exits the shell
 *
 * @shelldata: data relevant (status and args)
 * Return: 0 on success.
 */
int shell_exiter(shelldata_t *shelldata)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (shelldata->args[1] != NULL)
	{
		ustatus = _atoio(shelldata->args[1]);
		is_digit = _isdigito(shelldata->args[1]);
		str_len = _strleno(shelldata->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			error_getter(shelldata, 2);
			shelldata->status = 2;
			return (1);
		}
		shelldata->status = (ustatus % 256);
	}
	return (0);
}

