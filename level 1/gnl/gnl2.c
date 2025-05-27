char *get_next_line(int fd) // it reads from fd
{ // make sure to read what read takes
	static char *buffer;
	char *line; // until /n

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);                          "hello       \nworld\n42\n\0"
	
	buffer = read_line(fd , buffer);
	if (!buffer)
	{
		buffer = NULL; // test your code without it
		return (NULL);
	}

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

char *read_line(int fd, char *res) // it reads until buffer_size // res is static
{
	char *buffer;
	int bytes_read;

	if (!res) //??
	{
		res = malloc(1); // read again the difference between malloc and calloc
		res[0] = '\0';
	}
	if (!res)
		return (NULL);

	buffer = malloc (BUFFER_ SIZE + 1);
	if (!buffer)
	{
		free (res);
		return (NULL);
	}

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);

        if (bytes_read == -1);
        {
		free (res);
		res = NULL;
		free(buffer);
		return (NULL);
        }
        buffer[bytes_read] = '\0';

		res = join_str(res, buffer, bytes_read);
        if (!res)
        {
            free(res);
		free (buffer);
			return (NULL);
        }

        if (ft_strchr(buffer, '\n'))
			break ;
	}
	free (buffer)
	return (res);
}

int ft_strchr(const char *s, char c) // what does it do?
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == c)
            return (1);
        i++;
    }
    return 0;
}

char *join_str(char *res, char *buffer, int bytes_read) //char *buf?
{
	char *temp; // hay eli hoon sho betmathel?

	temp = ft_strjoin(res, buffer);
	if (!temp)
		return (NULL);
	free (res);
	return (temp);
}

char *ft_strjoin(char *s1, char *s2)
{ // how does this function work exactly?
    char *res; // hay eli ra7 terja3
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
        res[i++] = s2[j++]; //??
    res[i] = '\0';
    return (res);
}

char *set_line(char *buffer)
{
    char *line;
    int i;
    int j;

    i = 0;
    if (!buffer)
        return (NULL);
    while (buffer[i] && buffer[i] != '\n')
        i++;
    
    line = malloc (i + 2);
    if (!line)
        return (NULL);
    
    j = 0;
    while (j < i + 2)
        line[j++] = '\0'; //?
    
    i = 0;
    while (buffer[i] != '\0' && buffer[i] != '\n')
    {
        line[i] = buffer[i];
        i++;
    }
    if (buffer[i] =='\n') //??
        line[i] = '\n';
    return (line);
}

char *set_next(char *buffer)
{
    char *line;
    int i;
    int j;

    i = 0;
    while (buffer[i] != '\0' && buffer[i] != '\n')
        i++;
    if (buffer[i] == '\n')
        i++;
    if (!buffer[i])
    {
        free(buffer);
        buffer = NULL;
        return (NULL);
    }
    line = malloc(ft_strlen(buffer) - i + 1); //?
    if (!line)
    {
        free(buffer);
        buffer = NULL;
        return (NULL);
    }
    j = 0;
    while (buffer[i] != '\0')
        line[j++] = buffer[i++]; //??
    line[j] = '\0';
    free(buffer);
    return (line);
}

int ft_strlen(char *s)
{
    int i = 0;

    while (s[i])
        i++;
    return (i);
}

// set_next and set_line are almost the same in the syntax