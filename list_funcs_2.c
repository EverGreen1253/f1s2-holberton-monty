#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "monty.h"

/**
 * pop - pop the top item in the stack
 * @head: head of list
 * @n: unused
 *
 * Return: nothing
 */
void pop(stack_t **head, unsigned int n)
{
	(void)n;

	stack_t *curr;

	curr = *head;

	if (curr->next != NULL)
	{
		*head = curr->next;
		(*head)->prev = NULL;
	}
	else
		*head = NULL;

	free(curr);
}

/**
 * swap - swaps 2 elems in the stack
 * @head: head of list
 * @n: unused
 *
 * Return: nothing
 */
void swap(stack_t **head, unsigned int n)
{
	(void)n;

	int temp = (*head)->n;

	(*head)->n = (*head)->next->n;
	(*head)->next->n = temp;
}

/**
 * add - add the top 2 items in the stack
 * @head: head of list
 * @n: unused
 *
 * Return: nothing
 */
void add(stack_t **head, unsigned int n)
{
	(void)n;

	int temp = (*head)->n;

	temp = temp + (*head)->next->n;
	(*head)->next->n = temp;

	pop(head, n);
}

/**
 * nop - does nothing
 * @head: head of list
 * @n: unused
 *
 * Return: nothing
 */
void nop(stack_t **head, unsigned int n)
{
	(void)head;
	(void)n;
}

