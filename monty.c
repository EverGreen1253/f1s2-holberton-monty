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
	char *errmsg = "USAGE: monty file\n", *s, *n, *o;
	int bufsize = 65535;
	char buffer[bufsize];

	if (ac != 2)
	{
		write(2, errmsg, strlen(errmsg));
		exit(EXIT_FAILURE);
	}

	fp = fopen(av[1], "r");

	s = fgets(buffer, bufsize, fp);
	while (s != NULL)
	{
		n = strtrim(s);
		// printf("n - %s", n);
		o = remove_internal_spaces(n);
		printf("%s", o);
		free(n);
		free(o);

		s = fgets(buffer, bufsize, fp);
	}
	fclose(fp);

	return(0);
}

