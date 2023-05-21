#include "main.h"

/**
 * check_current_dir - checks ":" if is in the current directory.
 * @path: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int check_current_dir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * locate_comand - locates a command
 *
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *locate_comand(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdupo(path);
		len_cmd = _strleno(cmd);
		token_path = _strtoko(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (check_current_dir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strleno(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpyo(dir, token_path);
			_strcato(dir, "/");
			_strcato(dir, cmd);
			_strcato(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtoko(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * check_executable - determines if is an executable
 *
 * @datash: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int check_executable(shelldata_t *datash)
{
	struct stat st;
	int i;
	char *input;

	input = datash->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	error_getter(datash, 127);
	return (-1);
}

/**
 * check_permissions - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @datash: data structure
 * Return: 1 if there is an error, 0 if not
 */
int check_permissions(char *dir, shelldata_t *datash)
{
	if (dir == NULL)
	{
		error_getter(datash, 127);
		return (1);
	}

	if (_strcmpo(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			error_getter(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			error_getter(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * exec_command - executes command lines
 *
 * @datash: data relevant (args and input)
 * Return: 1 on success.
 */
int exec_command(shelldata_t *datash)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = check_executable(datash);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = locate_comand(datash->args[0], datash->_environ);
		if (check_permissions(dir, datash) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = locate_comand(datash->args[0], datash->_environ);
		else
			dir = datash->args[0];
		execve(dir + exec, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datash->status = state / 256;
	return (1);
}

