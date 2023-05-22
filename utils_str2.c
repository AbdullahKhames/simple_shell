#include "main.h"

/**
 * _strdupo - duplicates a str in the heap.
 * @s: Type char point str.
 * Return: duplicated str.
 */
char *_strdupo(const char *s)
{
char *new;
size_t len;

len = _strleno(s);
new = malloc(sizeof(char) * (len + 1));
if (new == NULL)
return (NULL);
_memcpyo(new, s, len + 1);
return (new);
}

/**
 * _strleno - Returns the lenght of a str.
 * @s: Type char point.
 * Return: Always 0.
 */
int _strleno(const char *s)
{
int len;

for (len = 0; s[len] != 0; len++)
{
}
return (len);
}

/**
 * cmp_charso - compare chars of strings
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int cmp_charso(char str[], const char *delim)
{
unsigned int i, j, k;

for (i = 0, k = 0; str[i]; i++)
{
for (j = 0; delim[j]; j++)
{
if (str[i] == delim[j])
{
k++;
break;
}
}
}
if (i == k)
return (1);
return (0);
}

/**
 * _strtoko - splits a string by some delimiter.
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: string splited.
 */
char *_strtoko(char str[], const char *delim)
{
static char *splitted, *str_end;
char *str_start;
unsigned int i, bool;

if (str != NULL)
{
if (cmp_charso(str, delim))
return (NULL);
splitted = str; /*Store first address*/
i = _strleno(str);
str_end = &str[i]; /*Store last address*/
}
str_start = splitted;
if (str_start == str_end) /*Reaching the end*/
return (NULL);

for (bool = 0; *splitted; splitted++)
{
/*Breaking loop finding the next token*/
if (splitted != str_start)
if (*splitted && *(splitted - 1) == '\0')
break;
/*Replacing delimiter for null char*/
for (i = 0; delim[i]; i++)
{
if (*splitted == delim[i])
{
*splitted = '\0';
if (splitted == str_start)
str_start++;
break;
}
}
if (bool == 0 && *splitted) /*Str != Delim*/
bool = 1;
}
if (bool == 0) /*Str == Delim*/
return (NULL);
return (str_start);
}

/**
 * _isdigito - defines if str passed is a num
 *
 * @s: input str
 * Return: 1 if string is a num 0 in other case.
 */
int _isdigito(const char *s)
{
unsigned int i;

for (i = 0; s[i]; i++)
{
if (s[i] < 48 || s[i] > 57)
return (0);
}
return (1);
}
