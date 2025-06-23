#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int buffer_read;
    static int buffer_pos;
    char *line;
    int i = 0;
    int line_size = 70000;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    line = (char *)malloc(sizeof(char) * line_size);
    if (!line)
        return (NULL);
    while (1)
    {
        if (buffer_pos >= buffer_read)
        {
            buffer_read = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;
            if (buffer_read == 0)
                break;
            else if (buffer_read < 0)
            {
                free(line);
                return (NULL);
            }
        }
        line[i++] = buffer[buffer_pos++];
        if (line[i - 1] == '\n')
        {
            break;
        }
    }
    line[i] = '\0';
    if (i == 0)
    {
        free(line);
        return (NULL);
    }
    return (line);
}

int main(void)
{
	int fd = open("test.txt", O_RDONLY);
    char *line = get_next_line(fd);

    if (fd < 0)
		return 1;

	while (line)
	{
		printf("%s", line);
		free(line);
        line = get_next_line(fd);
	}
	close(fd);
}