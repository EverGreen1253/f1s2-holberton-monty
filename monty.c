#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "monty.h"

/**
 * main - monty
 * @ac: number of arguments
 * @av: array of arguments
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	instruction_t ops[] = {
		{"u", push}, {"a", pall}, {"i", pint}, {"o", pop},
		{"w", swap}, {"d", add}, {"n", nop}
	};
	stack_t *stack = NULL;
	FILE *fp = NULL;
	char *s, *n, *o = NULL;
	int bufsize = 65535, line = 1;
	char buffer[bufsize];

	if (ac != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	fp = fopen(av[1], "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}

	s = fgets(buffer, bufsize, fp);
	while (s != NULL)
	{
		n = strtrim(s);
		if (n != NULL)
		{
			// o = remove_internal_spaces(n);
			// free(n);
			run_cmd(fp, line, n, ops, &stack);
			free(o);
		}
		s = fgets(buffer, bufsize, fp);
		line++;
	}
	free_list(stack);
	fclose(fp);
	return (0);
}

/**
 * run_cmd - run the cmd on the line
 * @fp: file pointer
 * @line: the line number of the script being run
 * @o: the line with the cmd
 * @ops: array for pointer functions
 * @stack: the stack
 *
 * Return: nothing
 */
void run_cmd(FILE *fp, int line, char *o, instruction_t *ops, stack_t **stack)
{
	int i = 0, value;
	char *temp, *cmd, *val, letter;

	if (o != NULL && o[0] == '$')
		die('0', fp, line, o, stack);

	temp = strtok(o, "$");
	cmd = strtok(temp, " ");
	cmd[strcspn(cmd, "\r\n")] = 0;

	letter = is_valid_cmd(cmd);
	if (letter == '0')
		die('0', fp, line, o, stack);

	value = line;
	if (letter == 'u') /* push */
	{
		val = strtok(NULL, " ");
		if ((val == NULL) || (strlen(val) == 0) || (is_valid_val(val) == 0))
			die(letter, fp, line, o, stack);

		value = atoi(val);
	}

	if ((*stack == NULL) && ((letter == 'i') || (letter == 'o')))
		die(letter, fp, line, o, stack);

	if ((*stack == NULL || (*stack)->next == NULL) &&
		line <= 2 && ((letter == 'w') || (letter == 'd')))
		die(letter, fp, line, o, stack);

	while (i < 7) /* hardcoded num of funcs */
	{
		if (*ops[i].opcode == letter)
			ops[i].f(stack, value);

		i++;
	}
}

/**
 * die - just die
 * @letter: the letter
 * @fp: file pointer
 * @line: line number
 * @o: the string for the line
 * @stack: the stack
 *
 * Return: nothing
 */
void die(char letter, FILE *fp, int line, char *o, stack_t **stack)
{
	if (letter == '0')
		fprintf(stderr, "L%d: unknown instruction %s\n", line, o);

	if (letter == 'u')
		fprintf(stderr, "L%d: usage: push integer\n", line);

	if (letter == 'i')
		fprintf(stderr, "L%d: can't pint, stack empty\n", line);

	if (letter == 'o')
		fprintf(stderr, "L%d: can't pop an empty stack\n", line);

	if (letter == 'w')
		fprintf(stderr, "L%d: can't swap, stack too short\n", line);

	if (letter == 'd')
		fprintf(stderr, "L%d: can't add, stack too short\n", line);

	free(o);
	free_list(*stack);

	fclose(fp);
	exit(EXIT_FAILURE);
}

/**
 * is_valid_cmd - does what it says
 * @c: the cmd to check
 *
 * Return: 0 or 1
 */
char is_valid_cmd(char *c)
{
	if (strcmp(c, "push") == 0)
		return ('u');

	if (strcmp(c, "pall") == 0)
		return ('a');

	if (strcmp(c, "pint") == 0)
		return ('i');

	if (strcmp(c, "pop") == 0)
		return ('o');

	if (strcmp(c, "swap") == 0)
		return ('w');

	if (strcmp(c, "add") == 0)
		return ('d');

	if (strcmp(c, "nop") == 0)
		return ('n');

	return ('0');
}

/**
 * is_valid_val - does what it says
 * @v: the value to check
 *
 * Return: 0 or 1
 */
int is_valid_val(char *v)
{
	int i = 0;

	v[strcspn(v, "\r\n")] = 0;
	while (v[i] != '\0')
	{
		if (!(v[i] == 45 || ((v[i] >= 48) && (v[i] <= 57))))
		{
			/* printf("%c", v[i]); */
			return (0);
		}
		i++;
	}
	return (1);
}
