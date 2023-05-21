#include "main.h"

/**
 * error_getter - calls the error according the builtin, syntax or permission
 * @datash: data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int error_getter(shelldata_t *datash, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = error_env(datash);
		break;
	case 126:
		error = error_path_126(datash);
		break;
	case 127:
		error = error_not_found(datash);
		break;
	case 2:
		if (_strcmpo("exit", datash->args[0]) == 0)
			error = error_exit_shell(datash);
		else if (_strcmpo("cd", datash->args[0]) == 0)
			error = error_get_cd(datash);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strleno(error));
		free(error);
	}

	datash->status = eval;
	return (eval);
}

