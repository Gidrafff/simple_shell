#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info structurw
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @patstr: the PATH string of the chars
 * @begin: begining index of the PATH
 * @end: ending index of the PATH
 *
 * Return: pointer to the new buffer
 */
char *dup_chars(char *patstr, int begin, int end)
{
	static char buf[1024];
	int a = 0, c = 0;

	for (c = 0, a = begin; a < end; a++)
		if (patstr[a] != ':')
			buf[c++] = patstr[a];
	buf[c] = 0;
	return (buf);
}

/**
 * find_path - Finds the cmd in the PATH string
 * @info: the info structure
 * @patstr: the PATH string to find
 * @cmd: the cmd to find in the PATH
 *
 * Return: full path of cmd if found or NULL if not found
 */
char *find_path(info_t *info, char *patstr, char *cmd)
{
	int a = 0, curr_pos = 0;
	char *path;

	if (!patstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!patstr[a] || patstr[a] == ':')
		{
			path = dup_chars(pathstr, curr_pos, a);
			if (!*path)
			_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!patstr[a])
				break;
			curr_pos = a;
		}
		a++;
	}
	return (NULL);
}
