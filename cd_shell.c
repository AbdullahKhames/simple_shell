#include <stdio.h>
#include <unistd.h>
#include "main.h"
#include <stdlib.h>

/**
 * cd_shello - changes current directory
 *
 * @datash: data relevant
 * Return: 1 on success
 */
int cd_shello(shelldata_t *datash)
{
char *dir;
int ishome, ishome2, isddash;

dir = datash->args[1];

if (dir != NULL)
{
ishome = _strcmpo("$HOME", dir);
ishome2 = _strcmpo("~", dir);
isddash = _strcmpo("--", dir);
}

if (dir == NULL || !ishome || !ishome2 || !isddash)
{
cd_to_homeo(datash);
return (1);
}

if (_strcmpo("-", dir) == 0)
{
cd_previouso(datash);
return (1);
}

if (_strcmpo(".", dir) == 0 || _strcmpo("..", dir) == 0)
{
cd_doto(datash);
return (1);
}

cd_too(datash);

return (1);
}
