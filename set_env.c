#include "main.h"

/**
 * copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strleno(name);
	len_value = _strleno(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpyo(new, name);
	_strcato(new, "=");
	_strcato(new, value);
	_strcato(new, "\0");

	return (new);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @shelldata: data structure (environ)
 * Return: no return
 */
void set_env(char *name, char *value, shelldata_t *shelldata)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; shelldata->_environ[i]; i++)
	{
		var_env = _strdupo(shelldata->_environ[i]);
		name_env = _strtoko(var_env, "=");
		if (_strcmpo(name_env, name) == 0)
		{
			free(shelldata->_environ[i]);
			shelldata->_environ[i] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	shelldata->_environ = _reallocdpo(shelldata->_environ, i, sizeof(char *) * (i + 2));
	shelldata->_environ[i] = copy_info(name, value);
	shelldata->_environ[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @shelldata: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(shelldata_t *shelldata)
{

	if (shelldata->args[1] == NULL || shelldata->args[2] == NULL)
	{
		error_getter(shelldata, -1);
		return (1);
	}

	set_env(shelldata->args[1], shelldata->args[2], shelldata);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @shelldata: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(shelldata_t *shelldata)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (shelldata->args[1] == NULL)
	{
		error_getter(shelldata, -1);
		return (1);
	}
	k = -1;
	for (i = 0; shelldata->_environ[i]; i++)
	{
		var_env = _strdupo(shelldata->_environ[i]);
		name_env = _strtoko(var_env, "=");
		if (_strcmpo(name_env, shelldata->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		error_getter(shelldata, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; shelldata->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = shelldata->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(shelldata->_environ[k]);
	free(shelldata->_environ);
	shelldata->_environ = realloc_environ;
	return (1);
}

