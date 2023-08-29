#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "monty.h"

/**
 * push - check the code
 * @head: pointer addr of head of list
 * @n: value to add
 *
 * Return: pointer to new node.
 */
void push(stack_t **head, unsigned int n)
{
	printf ("run push function\n");

	/*
        stack_t *node;

        node = malloc(sizeof(stack_t));
        if (node == NULL)
        {
                free_list(*head);
                exit(98);
        }

        node->n = n;

        if (*head == NULL)
        {
                node->next = NULL;
                node->prev = NULL;
                *head = node;
        }
        else
        {
                node->next = *head;
                (*head)->prev = node;
                *head = node;
        }
	*/
}

/**
 * free_list - check the code
 * @head: head of the list
 *
 * Return: nothing.
 */
void free_list(stack_t *head)
{
        stack_t *node;

        if (head != NULL)
        {
                node = head;
                if (node != NULL && node->next != NULL)
                {
                        free_node(node->next);
                }
                free(head);
        }
}

/**
 * free_node - frees mem usage by the node
 * @node: node to free up
 *
 * Return: nothing.
 */
void free_node(stack_t *node)
{
        if (node->next != NULL)
        {
                free_node(node->next);
        }
        free(node);
}

void pall(stack_t **head, unsigned int n)
{
	printf("run pall function\n");

	// FIXME:
}
