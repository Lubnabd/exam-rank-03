
#include "gnl.h"

char *ft_strdup(char *src) {
	char *dest;
	int i = 0;
	while (src[i])
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while(src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];
	static int buf_pos;
	static int buf_read;
	int i = 0;
	char line[70000];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	while (1) {
		if (buf_pos >= buf_read)
		{
			buf_read = read(fd, buffer, BUFFER_SIZE);
			if (buf_read <= 0)
				break;
			buf_pos = 0;
		}
		line[i++] = buffer[buf_pos++];
		if (buffer[buf_pos] == '\n')
			break;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}