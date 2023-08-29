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
		{"u", push}, {"a", pall}
	};
	stack_t *stack;
	FILE *fp = NULL;
	char *s, *n, *o = NULL;
	int bufsize = 65535, line = 1;
	char buffer[bufsize];

	stack = NULL;

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
		// printf("%s", n);

		/* empty lines is ok but give errors for empty params */

		if (n != NULL)
		{
			o = remove_internal_spaces(n);
			printf("%s", o);

			run_cmd(fp, line, o, ops, &stack);
			free(n);
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
 * @fp: File pointer
 * @line: the line number of the script being run
 * @o: the line with the cmd
 * @ops: array for pointer functions
 * @stack: the stack
 *
 * Return: 0 or 1
 */
void run_cmd(FILE *fp, int line, char *o, instruction_t *ops, stack_t **stack)
{
	int i = 0, value;
	char *temp, *cmd, *str_val;

	if (o != NULL && o[0] == '$')
	{
		fprintf(stderr, "L%d: unknown instruction %s", line, o);
		free(o);
		fclose(fp);
		exit(EXIT_FAILURE);
	}

	/* extract opcode here from line */
	temp = strtok(o, "$");
	cmd = strtok(temp, " ");
	value = line;
	if (cmd[1] == 'u')
	{
		str_val = strtok(NULL, " ");
		
		if ((str_val == NULL) || (strlen(str_val) == 0))
		{
			if (line > 1)
			{
				free_list(*stack);
			}

			fprintf(stderr, "L%d: usage: push integer\n", line);
			fclose(fp);
			exit(EXIT_FAILURE);
		}
		
		value = atoi(str_val);
	}

	/* printf("cmd to run %s %d\n", cmd, value); */

	while (i < 2)
	{
		if (*ops[i].opcode == cmd[1])
		{
			/* printf("Running cmd %s\n", cmd); */
			ops[i].f(stack, value);
		}
		i++;
	}
}

