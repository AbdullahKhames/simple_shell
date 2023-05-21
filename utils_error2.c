#include "main.h"
#include <errno.h>

/**
 * error_env - err mesag for env in get_env.
 * @datash: data relevant (counter, argu)
 * Return: err message.
 */
char *error_env(shelldata_t *datash)
{
int length;
char *error;
char *ver_str;
char *msg;

ver_str = utils_itoa(datash->counter);
msg = ": Unable to add/remove from environment\n";
length = _strlen(datash->av[0]) + _strlen(ver_str);
length += _strlen(datash->args[0]) + _strlen(msg) + 4;
error = malloc(sizeof(char) * (length + 1));
if (error == 0)
{
free(error);
free(ver_str);
return (NULL);
}

_strcpy(error, datash->av[0]);
_strcat(error, ": ");
_strcat(error, ver_str);
_strcat(error, ": ");
_strcat(error, datash->args[0]);
_strcat(error, msg);
_strcat(error, "\0");
free(ver_str);

return (error);
}
/**
 * error_path_126 - err message for path and fail denie permission.
 * @datash: data relevant (counter, argu).
 *
 * Return: The err string.
 */
char *error_path_126(shelldata_t *datash)
{
int length;
char *ver_str;
char *error;

ver_str = utils_itoa(datash->counter);
length = _strlen(datash->av[0]) + _strlen(ver_str);
length += _strlen(datash->args[0]) + 24;
error = malloc(sizeof(char) * (length + 1));
if (error == 0)
{
free(error);
free(ver_str);
return (NULL);
}
_strcpy(error, datash->av[0]);
_strcat(error, ": ");
_strcat(error, ver_str);
_strcat(error, ": ");
_strcat(error, datash->args[0]);
_strcat(error, ": Permission denied\n");
_strcat(error, "\0");
free(ver_str);
return (error);
}
