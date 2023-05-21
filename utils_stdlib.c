#include "main.h"

/**
 * get_leno - Get the lenght of a num.
 * @n: type int num.
 * Return: Lenght of a num.
 */
int get_leno(int n)
{
unsigned int n1;
int lenght = 1;

if (n < 0)
{
lenght++;
n1 = n * -1;
}
else
{
n1 = n;
}
while (n1 > 9)
{
lenght++;
n1 = n1 / 10;
}

return (lenght);
}
/**
 * utils_itoa - func convrt int to str.
 * @n: type int number
 * Return: String.
 */
char *utils_itoa(int n)
{
unsigned int n1;
int lenght = get_leno(n);
char *buffer;

buffer = malloc(sizeof(char) * (lenght + 1));
if (buffer == 0)
return (NULL);

*(buffer + lenght) = '\0';

if (n < 0)
{
n1 = n * -1;
buffer[0] = '-';
}
else
{
n1 = n;
}

lenght--;
do {
*(buffer + lenght) = (n1 % 10) + '0';
n1 = n1 / 10;
lenght--;
}
while (n1 > 0)
		;
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
oi = oi + ((*(s + i) - 48) * m);
m /= 10;
}
return (oi * pn);
}
