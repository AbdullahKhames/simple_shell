#include <stdio.h>
#include "main.h"

/**
 * _memcpyo - copies information between void point.
 * @newptr: destination poi.
 * @ptr: source pointr.
 * @size: size of the new point.
 *
 * Return: no return.
 */
void _memcpyo(void *newptr, const void *ptr, unsigned int size)
{
char *char_ptr = (char *)ptr;
char *char_newptr = (char *)newptr;
unsigned int i;

for (i = 0; i < size; i++)
char_newptr[i] = char_ptr[i];
}

/**
 * _realloco - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size, in bytes  of the allocate
 * @new_size: new size, in bytes, of new block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without cha
 * if malloc fails returns NULL.
 */
void *_realloco(void *ptr, unsigned int old_size, unsigned int new_size)
{
void *newptr;

if (ptr == NULL)
return (malloc(new_size));

if (new_size == 0)
{
free(ptr);
return (NULL);
}

if (new_size == old_size)
return (ptr);

newptr = malloc(new_size);
if (newptr == NULL)
return (NULL);

if (new_size < old_size)
_memcpyo(newptr, ptr, new_size);
else
_memcpyo(newptr, ptr, old_size);

free(ptr);
return (newptr);
}

/**
 * _reallocdpo - reallocates a memory block of a doub
 * @ptr: double pointer to the memory previ
 * @old_size: size, in bytes
 * @new_size: new size in bytes of the new memo
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **_reallocdpo(char **ptr, unsigned int old_size, unsigned int new_size)
{
char **newptr;
unsigned int i;

if (ptr == NULL)
return (malloc(sizeof(char *) * new_size));

if (new_size == old_size)
return (ptr);

newptr = malloc(sizeof(char *) * new_size);
if (newptr == NULL)
return (NULL);

for (i = 0; i < old_size; i++)
newptr[i] = ptr[i];

free(ptr);

return (newptr);
}
