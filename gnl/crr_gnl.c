#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

int	ft_strlen(char *s)
{
	int i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	ft_strchr(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int len1 = ft_strlen(s1), len2 = ft_strlen(s2), i = 0, j = 0;
	char *res = malloc(len1 + len2 + 1);

	if (!res) return (free(s1), NULL);
	while (i < len1)
		res[i++] = *s1++;
	while (j < len2)
		res[i++] = *s2++;
	res[i] = '\0';
	return (res - len1); // adjust pointer since s1 was incremented
}

char	*set_line(char *buf)
{
	int i = 0;
	while (buf[i] && buf[i] != '\n') i++;
	char *line = malloc(i + (buf[i] == '\n') + 1);
	if (!line) return NULL;
	for (int j = 0; j <= i; j++)
		line[j] = buf[j];
	line[i + (buf[i] == '\n')] = '\0';
	return line;
}

char	*set_next(char *buf)
{
	int i = 0, j = 0;
	while (buf[i] && buf[i] != '\n') i++;
	if (!buf[i]) return (free(buf), NULL);
	char *next = malloc(ft_strlen(buf + i + 1) + 1);
	if (!next) return (free(buf), NULL);
	while (buf[++i])
		next[j++] = buf[i];
	next[j] = '\0';
	free(buf);
	return next;
}

char	*read_file(int fd, char *res)
{
	char *buf = malloc(BUFFER_SIZE + 1);
	int br = 1;

	if (!buf) return free(res), NULL;
	while (br > 0 && !ft_strchr(res, '\n'))
	{
		br = read(fd, buf, BUFFER_SIZE);
		if (br <= 0) break;
		buf[br] = '\0';
		char *tmp = ft_strjoin(res, buf);
		if (!tmp) return free(buf), NULL;
		free(res);
		res = tmp;
	}
	free(buf);
	return (br < 0 ? free(res), NULL : res);
}

char	*get_next_line(int fd)
{
	static char *buffer;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	buffer = read_file(fd, buffer);
	if (!buffer) return NULL;
	line = set_line(buffer);
	buffer = set_next(buffer);
	return line;
}

int main(void)
{
	int fd = open("file.txt", O_RDONLY);
	char *line;

	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}
