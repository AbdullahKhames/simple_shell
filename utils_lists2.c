#include <stdio.h>
#include "main.h"
#include <stdlib.h>

/**
 * add_rvaro_node - add a var at the end
 * of a r_varo list.
 * @head: head of the linked list.
 * @lvaro: length of the var.
 * @val: value of the var.
 * @lval: length of the value.
 * Return: address of the head.
 */
r_varo *add_rvaro_node(r_varo **head, int lvaro, char *val, int lval)
{
r_varo *new, *temp;

new = malloc(sizeof(r_varo));
if (new == NULL)
return (NULL);

new->len_varo = lvaro;
new->val = val;
new->len_val = lval;

new->next = NULL;
temp = *head;

if (temp == NULL)
{
*head = new;
}
else
{
while (temp->next != NULL)
temp = temp->next;
temp->next = new;
}

return (*head);
}

/**
 * free_rvaro_list - frees a r_varo list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_rvaro_list(r_varo **head)
{
r_varo *temp;
r_varo *curr;

if (head != NULL)
{
curr = *head;
while ((temp = curr) != NULL)
{
curr = curr->next;
free(temp);
}
*head = NULL;
}
}
