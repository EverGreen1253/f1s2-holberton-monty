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
	char *s, *n, *o = NULL, *line_num, *cmd;
	int bufsize = 65535, line = 1, invalid = 0;
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
		/* printf("%s", n); */
		o = remove_internal_spaces(n);
		/* printf("%s", o); */

		free(n);

		run_cmd(fp, line, o, ops, &stack);
		free(o);

		s = fgets(buffer, bufsize, fp);
		line++;
	}
	free_list(stack);
	fclose(fp);

	return (0);
}

/**
 * run_cmd - run the cmd on the line
 * @o: the line with the cmd
 *
 * Return: 0 or 1
 */
void run_cmd(FILE *fp, int line, char *o, instruction_t *ops, stack_t **stack)
{
	int i = 0, value;
	char *temp, *cmd;

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

	/* extract push value if cmd is push */
	value = (cmd[1] == 'u') ? atoi(strtok(NULL, " ")) : line;

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

