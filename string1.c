#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination of the string
 * @src: the source to copy
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int a = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to be duplicated
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_putchar(str[a]);
		a++;
	}
}

/**
 * _putchar - writes the char b to stdout
 * @b: The char to print
 *
 * Return: On success 1.
 * On error, returned -1, and errno is set appropriately.
 */
int _putchar(char b)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (b == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buf, a);
		a = 0;
	}
	if (b != BUF_FLUSH)
		buf[a++] = b;
	return (1);
}
