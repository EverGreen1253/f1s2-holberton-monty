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
	FILE *fp = NULL;
	char *s, *n, *o = NULL, *line_num;
	int bufsize = 65535, line = 1, invalid = 0;
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
		/* printf("%s", n); */
		o = remove_internal_spaces(n);
		printf("%s", o);

		free(n);
		
		/* Check if command is invalid */
		invalid = is_invalid_cmd(o);
		if (invalid)
		{
			fprintf(stderr, "L%d: unknown instruction %s", line, o);
			free(o);
			fclose(fp);
			exit(EXIT_FAILURE);
		}

		/* Run the command here */
		// FIXME:

		free(o);

		s = fgets(buffer, bufsize, fp);
		line++;
	}
	fclose(fp);

	return(0);
}

int is_invalid_cmd(char *o)
{
	if (o != NULL && o[0] == '$')
	{
		return(1);
	}

	return(0);
}
