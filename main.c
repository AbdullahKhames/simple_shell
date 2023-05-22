#include "main.h"

/**
 * data_free - frees data structure
 *
 * @shelldata: data structure
 * Return: no return
 */
void data_free(shelldata_t *shelldata)
{
	unsigned int i;

	for (i = 0; shelldata->_environ[i]; i++)
	{
		free(shelldata->_environ[i]);
	}

	free(shelldata->_environ);
	free(shelldata->pid);
}

/**
 * data_set - Initialize data structure
 *
 * @shelldata: data structure
 * @av: argument vector
 * Return: no return
 */
void data_set(shelldata_t *shelldata, char **av)
{
	unsigned int i;

	shelldata->av = av;
	shelldata->input = NULL;
	shelldata->args = NULL;
	shelldata->status = 0;
	shelldata->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	shelldata->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		shelldata->_environ[i] = _strdupo(environ[i]);
	}

	shelldata->_environ[i] = NULL;
	shelldata->pid = utils_itoa(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	shelldata_t shelldata;
	(void) ac;

	signal(SIGINT, get_sigint);
	data_set(&shelldata, av);
	shell_looper(&shelldata);
	data_free(&shelldata);
	if (shelldata.status < 0)
		return (255);
	return (shelldata.status);
}
