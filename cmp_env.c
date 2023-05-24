#include "main.h"

/**
 * env_cmp - function to compare environment variables names
 * with the name passed.
 * @currentenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int env_cmp(const char *currentenv, const char *name)
{
	int i;

	for (i = 0; currentenv[i] != '='; i++)
	{
		if (currentenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenv - get an environment variable
 * @key: key of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *key, char **_environ)
{
	char *ptr_env;
	int i, mov;

	ptr_env = NULL;
	mov = 0;
	for (i = 0; _environ[i]; i++)
	{
		mov = env_cmp(_environ[i], key);
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - prints the evironment variables
 *
 * @shelldata: data relevant.
 * Return: 1 on success.
 */
int _env(shelldata_t *shelldata)
{
	int i, j;

	for (i = 0; shelldata->_environ[i]; i++)
	{

		for (j = 0; shelldata->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, shelldata->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	shelldata->status = 0;

	return (1);
}

