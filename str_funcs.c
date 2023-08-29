#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "monty.h"

/**
 * iswhitespace - evaluates if the char is whitespace
 * @c: the char to evaluate
 *
 * Return: 0 or 1
 */
int iswhitespace(char c)
{
	if ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r') || (c == '\f'))
	{
		return (1);
	}

	return (0);
}

/**
 * strtrim - trim the whitespace form the front and end of string
 * @s: the string to trim
 *
 * Return: trimmed string
 */
char *strtrim(char *s)
{
	size_t len = strlen(s), start = 0, end = len - 1, i;
	char *n;

	if (len == 0)
		return (s);

	while (iswhitespace(s[start]))
		start++;

	/* everything is white space */
	if (start == len)
	{
		return (NULL);
	}

	while (iswhitespace(s[end]))
		end--;

	/* printf("start - %lu, end - %lu, len - %lu\n", start, end, len); */

	i = 0;
	n = (char *) malloc(end - start + 3);
	if (n == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	while (i < (end - start + 1))
	{
		n[i] = s[start + i];
		i++;
	}

	n[i] = '\n';
	n[i + 1] = '\0';

	return (n);
}

/**
 * remove_internal_spaces - does what it says
 * @s: the string to work on
 *
 * Return: the optimised string
 */
char *remove_internal_spaces(char *s)
{
	int i = 0, j = 0, found = 0, len = 0;
	char *o = NULL;

	len = count_valid_cmd_chars(s);
	o = (char *) malloc(len + 1);
	if (o == NULL)
	{
		free(s);
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	while (s[i] != '\0')
	{
		if (s[i] == ' ')
		{
			if (found == 0)
			{
				o[j] = s[i];
				found = 1;
				j++;
			}
		}
		else
		{
			if (s[i] == '$' && found == 1)
			{
				j--;
				o[j] = s[i];
			}

			o[j] = s[i];
			found = 0;
			j++;
		}

		i++;
	}
	o[j] = '\0';
	return (o);
}

/**
 * count_valid_cmd_chars - does what it says
 * @s: the string
 *
 * Return: num of chars we want for the cmd
 */
int count_valid_cmd_chars(char *s)
{
	int i = 0, len = 0, found = 0;

	while (s[i] != '\0')
	{
		if (s[i] == ' ')
		{
			if (found == 0)
			{
				found = 1;
				len++;
			}
		}
		else
		{
			/* space(s) before the final $ */
			/* e.g. 'pall   $' or 'push  6  $' */
			if (s[i] == '$' && found == 1)
			{
				len--;
			}

			found = 0;
			len++;
		}

		i++;
	}

	return (i);
}
