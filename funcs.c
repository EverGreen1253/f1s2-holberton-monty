#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "monty.h"

/**
 * iswhitespace - evaluates if the char is whitespace
 * @ch: the char to evaluate
 *
 * Return: 0 or 1
 */
int iswhitespace(char ch)
{
    if ((ch == ' ') || (ch == '\t') || (ch == '\n') || (ch == '\r') || (ch == '\f'))
        return 1;

    return 0;
}

/**
 * strtrim - trim the whitespace form the front and end of string
 * @s: the string to trim
 *
 * Return: trimmed string
 */
char *strtrim(char *s)
{
        size_t len = strlen(s);
        size_t start = 0;
        size_t end = len - 1;
        size_t i;
        char *n;

        if (len == 0)
        {
                return s;
        }

        while (iswhitespace(s[start]))
        {
                start++;
        }

        while (iswhitespace(s[end]))
        {
                end--;
        }

        i = 0;
        n = malloc(end - start + 3);
        while(i < (end - start + 1))
        {
                n[i] = s[start + i];
                i++;
        }
        n[i] = '\n';
        n[i + 1] = '\0';

        return n;
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

        while(s[i] != '\0')
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

        o = malloc(len + 2);

        i = 0;
        found = 0;
        while(s[i] != '\0')
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
        o[j + 1] = '\0';

        /* printf("new len - %d\n", len); */

        return o;
}
