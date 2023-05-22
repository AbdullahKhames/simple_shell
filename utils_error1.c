#include "main.h"

/**
 * strcat_cd - funct that concatates the message for cd err
 *
 * @datash: data relevant (dirct)
 * @mssg: message to print
 * @error: out put message
 * @ver_str: counter line
 * Return: err message
 */
char *strcat_cd(shelldata_t *datash, char *mssg, char *error, char *ver_str)
{
char *illegal_flag;

_strcpyo(error, datash->av[0]);
_strcato(error, ": ");
_strcato(error, ver_str);
_strcato(error, ": ");
_strcato(error, datash->args[0]);
_strcato(error, mssg);
if (datash->args[1][0] == '-')
{
illegal_flag = malloc(3);
illegal_flag[0] = '-';
illegal_flag[1] = datash->args[1][1];
illegal_flag[2] = '\0';
_strcato(error, illegal_flag);
free(illegal_flag);
}
else
{
_strcato(error, datash->args[1]);
}

_strcato(error, "\n");
_strcato(error, "\0");
return (error);
}

/**
 * error_get_cd - err message for cd command in get_cd
 * @datash: data relev
 * Return: Err message
 */
char *error_get_cd(shelldata_t *datash)
{
int length, len_id;
char *error, *ver_str, *mssg;

ver_str = utils_itoa(datash->counter);
if (datash->args[1][0] == '-')
{
mssg = ": Illegal option ";
len_id = 2;
}
else
{
mssg = ": can't cd to ";
len_id = _strleno(datash->args[1]);
}

length = _strleno(datash->av[0]) + _strleno(datash->args[0]);
length += _strleno(ver_str) + _strleno(mssg) + len_id + 5;
error = malloc(sizeof(char) * (length + 1));

if (error == 0)
{
free(ver_str);
return (NULL);
}

error = strcat_cd(datash, mssg, error, ver_str);

free(ver_str);

return (error);
}

/**
 * error_not_found - generic err message for command not found
 * @datash: data relevant (counter, argu)
 * Return: Err message
 */
char *error_not_found(shelldata_t *datash)
{
int length;
char *error;
char *ver_str;

ver_str = utils_itoa(datash->counter);
length = _strleno(datash->av[0]) + _strleno(ver_str);
length += _strleno(datash->args[0]) + 16;
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
_strcato(error, ": not found\n");
_strcato(error, "\0");
free(ver_str);
return (error);
}

/**
 * error_exit_shell - generic err message for exit in get_exit
 * @datash: data relevant (count, argume)
 *
 * Return: Err message
 */
char *error_exit_shell(shelldata_t *datash)
{
int length;
char *error;
char *ver_str;

ver_str = utils_itoa(datash->counter);
length = _strleno(datash->av[0]) + _strleno(ver_str);
length += _strleno(datash->args[0]) + _strleno(datash->args[1]) + 23;
error = malloc(sizeof(char) * (length + 1));
if (error == 0)
{
free(ver_str);
return (NULL);
}
_strcpyo(error, datash->av[0]);
_strcato(error, ": ");
_strcato(error, ver_str);
_strcato(error, ": ");
_strcato(error, datash->args[0]);
_strcato(error, ": Illegal number: ");
_strcato(error, datash->args[1]);
_strcato(error, "\n\0");
free(ver_str);

return (error);
}
