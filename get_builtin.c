#include "main.h"

/**
 * get_builtin - function to get builtin commands
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(shelldata_t *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", shell_exiter },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shello },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmpo(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}

