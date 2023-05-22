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
length = _strleno(datash->av[0]) + _strleno(ver_str);
length += _strleno(datash->args[0]) + _strleno(msg) + 4;
error = malloc(sizeof(char) * (length + 1));
if (error == 0)
{
free(error);
free(ver_str);
return (NULL);
}

_strcpyo(error, datash->av[0]);
_strcato(error, ": ");
_strcato(error, ver_str);
_strcato(error, ": ");
_strcato(error, datash->args[0]);
_strcato(error, msg);
_strcato(error, "\0");
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
length = _strleno(datash->av[0]) + _strleno(ver_str);
length += _strleno(datash->args[0]) + 24;
error = malloc(sizeof(char) * (length + 1));
if (error == 0)
{
free(error);
free(ver_str);
return (NULL);
}
_strcpyo(error, datash->av[0]);
_strcato(error, ": ");
_strcato(error, ver_str);
_strcato(error, ": ");
_strcato(error, datash->args[0]);
_strcato(error, ": Permission denied\n");
_strcato(error, "\0");
free(ver_str);
return (error);
}
