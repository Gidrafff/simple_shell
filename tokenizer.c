#include "shell.h"

/**
 * **strtow - splits a string into words, repeated delim are ignored
 * @str: the input of the string
 * @b: the delim string to split
 * Return: a pointer to the array of the strings, or NULL on failure
 */
char **strtow(char *str, char *b)
{
	int a, h, l, n, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!b)
		b = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], b) && (is_delim(str[a + 1], b) || !str[a + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, h = 0; h < numwords; h++)
	{
		while (is_delim(str[a], b))
			a++;
		l = 0;
		while (!is_delim(str[a + l], b) && str[a + l])
			l++;
		s[h] = malloc((l + 1) * sizeof(char));
		if (!s[h])
		{
			for (l = 0; l < h; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			s[h][n] = str[a++];
		s[h][n] = 0;
	}
	s[h] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input of the string
 * @b: the delimeter to split
 * Return: a pointer to the array of the strings, or NULL if failure
 */
char **strtow2(char *str, char b)
{
	int a, h, l, n, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != b && str[a + 1] == b) ||
				(str[a] != b && !str[a + 1]) || str[a + 1] == b)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, h = 0; h < numwords; h++)
	{
		while (str[a] == b && str[a] != b)
			a++;
		l = 0;
		while (str[a + l] != b && str[a + l] && str[a + l] != b)
			l++;
		s[h] = malloc((l + 1) * sizeof(char));
		if (!s[h])
		{
			for (l = 0; l < h; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			s[h][n] = str[a++];
		s[h][n] = 0;
	}
	s[h] = NULL;
	return (s);
}
