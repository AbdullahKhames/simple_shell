#include <stdio.h>
#include <unistd.h>
#include "main.h"

/**
 * add_sepo_node_end - adds a separar found
 * of a sepo_list.
 * @head: head of the link list.
 * @sepo: seperator found (; | &).
 * Return: address of the head.
 */
sepo_list *add_sepo_node_end(sepo_list **head, char sepo)
{
sepo_list *new, *temp;

new = malloc(sizeof(sepo_list));
if (new == NULL)
return (NULL);

new->separator = sepo;
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
 * free_sepo_list - frees a sepo_list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_sepo_list(sepo_list **head)
{
sepo_list *temp;
sepo_list *curr;

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

/**
 * add_line_node_end - adds a command line at the end
 * of a line_list.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
line_list *add_line_node_end(line_list **head, char *line)
{
line_list *new, *temp;

new = malloc(sizeof(line_list));
if (new == NULL)
return (NULL);

new->line = line;
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
 * free_line_list - frees a line_list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_line_list(line_list **head)
{
line_list *temp;
line_list *curr;

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
