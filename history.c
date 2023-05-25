#include "shell.h"

/**
 * get_history_file - Gets the history file path
 * @info: Parameter structure
 * Return: allocated string containing history file path
 */
char *get_history_file(info_t *info)
{
	char *buffer, *directory;

	directory = _getenv(info, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	_strcpy(buffer, directory);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - Create a file, or Appends to an already existing file.
 * @info: the parameter structure.
 * Return: 1 if success,
 * Otherwise -1 if failure
 */
int write_history(info_t *info)
{
	ssize_t filedescriptor;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	filedescriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (filedescriptor == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, filedescriptor);
		_putfd('\n', filedescriptor);
	}
	_putfd(BUF_FLUSH, filedescriptor);
	close(filedescriptor);
	return (1);
}

/**
 * read_history - Reads history from the file path.
 * @info: the parameter structure
 * Return: histcount if success,
 * Otherwise 0 if failure
 */
int read_history(info_t *info)
{
	int a, last = 0, linecount = 0;
	ssize_t fd, rdlen, filesize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
	return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		filesize = st.st_size;
	if (filesize < 2)
		return (0);
	buf = malloc(sizeof(char) * (filesize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, filesize);
	buf[filesize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (a = 0; a < filesize; a++)
		if (buf[a] == '\n')
		{
			buf[a] = 0;
			build_history_list(info, buf + last, linecount++);
			last = a + 1;
		}
	if (last != a)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Adds entry to a history linked list
 * @info: Structure containing potential arguments.
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0 (Success)
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - function to update the numbering of the linked list.
 * @info: Structure containing potentially holds arguments.
 *
 * Return: The value of  histcount.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int count = 0;

	while (node)
	{
		node->num = count++;
		node = node->next;
	}
	info->histcount = count;
	return (count);
}
