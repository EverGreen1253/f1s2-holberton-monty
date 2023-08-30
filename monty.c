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
	instruction_t ops[] = {{"u", push}, {"a", pall}};
	stack_t *stack = NULL;
	FILE *fp = NULL;
	char *s, *n, *o = NULL;
	int bufsize = 65535, line = 1, result = 0;
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

	result = 0;
	s = fgets(buffer, bufsize, fp);
	while (s != NULL)
	{
		n = strtrim(s);
		/* printf("%s", n); */
		if (n != NULL)
		{
			o = remove_internal_spaces(n);
			/* printf("%s", o); */
			result = run_cmd(fp, line, o, ops, &stack);
			if (result == -1)
			{
				fprintf(stderr, "L%d: unknown instruction %s\n", line, o);
			}
			else if (result == -2)
			{
				fprintf(stderr, "L%d: usage: push integer\n", line);
			}

			free(n);
			free(o);

			if (result < 0)
			{
				if (line > 0)
				{
					free_list(stack);
				}

				fclose(fp);
				exit(EXIT_FAILURE);
			}

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
 * @fp: File pointer
 * @line: the line number of the script being run
 * @o: the line with the cmd
 * @ops: array for pointer functions
 * @stack: the stack
 *
 * Return: 0 or -1 or -2
 */
int run_cmd(FILE *fp, int line, char *o, instruction_t *ops, stack_t **stack)
{
	int i = 0, value;
	char *temp, *cmd, *val;

	if (o != NULL && o[0] == '$')
	{
		return (-1);
	}

	temp = strtok(o, "$");
	cmd = strtok(temp, " ");
	cmd[strcspn(cmd, "\r\n")] = 0;

	if (is_valid_cmd(cmd) == 0)
	{
		return (-1);
	}

	value = line;
	if (strcmp(cmd, "push") == 0)
	{
		val = strtok(NULL, " ");
		if ((val == NULL) || (strlen(val) == 0) || (is_valid_val(val) == 0))
		{
			return (-2);
		}
		value = atoi(val);
	}

	while (i < 2)
	{
		if (*ops[i].opcode == cmd[1])
			ops[i].f(stack, value);

		i++;
	}

	return (0);
}

/**
 * is_valid_cmd - does what it says
 * @c: the cmd to check
 *
 * Return: 0 or 1
 */
int is_valid_cmd(char *c)
{
	if ((strcmp(c, "push") == 0) || (strcmp(c, "pall") == 0))
	{
		return (1);
	}
	return (0);
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
