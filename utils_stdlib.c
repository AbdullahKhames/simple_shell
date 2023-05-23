#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * get_leno - Get the length of a num.
 * @n: type int num.
 * Return: Length of a num.
 */
int get_leno(int n)
{
unsigned int n1;
int length = 1;

if (n < 0)
{
length++;
n1 = n * -1;
}
else
{
n1 = n;
}

while (n1 > 9)
{
length++;
n1 = n1 / 10;
}

return (length);
}

/**
 * utils_itoa - func convert int to str.
 * @n: type int number
 * Return: String.
 */
char *utils_itoa(int n)
{
unsigned int n1;
int length = get_leno(n);
char *buffer;

buffer = malloc(sizeof(char) * (length + 1));
if (buffer == NULL)
return (NULL);

buffer[length] = '\0';

if (n < 0)
{
n1 = n * -1;
buffer[0] = '-';
}
else
{
n1 = n;
}

length--;
do {
buffer[length] = (n1 % 10) + '0';
n1 = n1 / 10;
length--;
} while (n1 > 0);

return (buffer);
}

/**
 * _atoio - converts a string to an integer.
 * @s: input str
 * Return: int
 */
int _atoio(char *s)
{
unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

while (*(s + count) != '\0')
{
if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
break;

if (*(s + count) == '-')
pn *= -1;

if ((*(s + count) >= '0') && (*(s + count) <= '9'))
{
if (size > 0)
m *= 10;
size++;
}
count++;
}

for (i = count - size; i < count; i++)
{
oi = oi + ((*(s + i) - '0') * m);
m /= 10;
}

return (oi *pn); }
