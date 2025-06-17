#include "gnl.h"

int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return (i);
}

// joins two strings together before \n
char *ft_strjoin(char *s1, char *s2)
{
    char *res; // return value
    int len1;
    int len2;
    int i;
    int j;

    if (!s1 || !s2)
        return (NULL);
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);

    res = malloc(len1 + len2 + 1);
    if (!res)
        return (NULL);
    
    i = 0;
    while (s1[i])
    {
        res[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
    res[i] = '\0';
    return (res);
}

char *join_str(char *res, char *buffer)
{
    char *tmp; // temporary pointer to store the result of joining res and buffer

    tmp = ft_strjoin(res, buffer);
    if (!tmp)
    {
        free(res);
        res = NULL; //not sure?
        return (NULL);
    }
    free(res);
    return (tmp);
}

int ft_strchr(const char *s, char c)
{
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == c)
            return 1; // true
        i++;
    }
    return 0;
}

char *read_line(int fd, char *res) // res holds what was read so far // it reads until buffer_size // res is static
{
    int bytes_read;
    char *buffer;

    if (!res)
    {
        res = malloc(1);
        res[0] = '\0';
    }
    if (!res)
        return (NULL);

    buffer = malloc (BUFFER_SIZE + 1); // i will read till here everytime
    if (!buffer)
    {
        free(res);
        res = NULL;
        return (NULL);
    }

    bytes_read = 1;
    while (bytes_read > 0)
    {
        bytes_read = read (fd, buffer , BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(res);
            res = NULL;
            free(buffer);
            return (NULL);
        }
        buffer[bytes_read] = '\0';

        res = join_str (res, buffer);
        if (!res)
        {
            free(buffer);
            return (NULL);
        }

        if (ft_strchr(buffer, '\n'))
            break ;
    }
    free(buffer);
    return (res);
}

char *set_line (char *buffer) // buffer is static
{
    char *line;
    int i;
    int j;

    i = 0;
    if(!buffer[i])
        return (NULL);
    while (buffer[i] && buffer[i] != '\n')
        i++;

    line = malloc(i + 2); //important
    if (!line)
        return (NULL);

    /*j = 0;
    while ( j < i + 2)
    {
        line[j] = '\0';
        j++;
    }*/
    i = 0;
    while (buffer[i] && buffer[i] != '\n')
    {
        line[i] = buffer[i];
        i++;
    }
    if (buffer[i] == '\n')
        line[i] = '\n';
    return (line);
}

char *set_next(char *buffer)
{
    char *line;
    int i = 0;
    int j;

    if (!buffer)
        return (NULL);
    while (buffer[i] && buffer[i] != '\n')
        i++;
    if(buffer[i] == '\n')
        i++;

    if (!buffer[i])
    {
        free(buffer);
        buffer = NULL;
        return (NULL);
    }
    line = malloc(ft_strlen(buffer) - i + 1);
    if (!line)
    {
        free(buffer);
        buffer = NULL;
        return (NULL);
    }
    j = 0;
    while (buffer[i])
        line[j++] = buffer[i++];
    line[j] = '\0';
    free(buffer);
    return (line);
}

char *get_next_line(int fd) // it reads from fd
{
    static char *buffer;
    char *line; // until /n

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = read_line(fd, buffer);
    if (!buffer)
        return (NULL);

    line = set_line(buffer);
    if (!line)
    {
        free(buffer);
        buffer = NULL;
        return (NULL);
    }
    buffer = set_next(buffer);
    return (line);
}

int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return 1;
	}

	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return 0;
}