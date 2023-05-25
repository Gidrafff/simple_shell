#include "shell.h"

/**
 * _strlen - returns the string length
 * @r: the string length to check
 *
 * Return: integer length of the string
 */
int _strlen(char *r)
{
	int a = 0;

	if (!r)
		return (0);

	while (*r++)
		a++;
	return (a);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @r1: the first strang to compare
 * @r2: the second strang to compare
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *r1, char *r2)
{
	while (*r1 && *r2)
	{
		if (*r1 != *r2)
			return (*r1 - *r2);
		r1++;
		r2++;
	}
	if (*r1 == *r2)
		return (0);
	else
		return (*r1 < *r2 ? -1 : 1);
}

/**
 * starts_with - checks if the needle starts with in a haystack
 * @haystack: string to search in the haystack
 * @needle: the substring to find in the haystack
 *
 * Return: Address of the next character of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
		*dest = *src;
		return (ret);
}
