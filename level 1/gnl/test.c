# define BUFFER_SIZE 42

int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

int ft_strchr(const char *s, char c)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == c)
            return 1;
        i++;
    }
    return 0;
}

char *ft_strjoin (char *s1, char *s2)
{
    char *res; ////******* */
    int i = 0;
    int j = 0;
    int len1 = ft_strlen(s1);
    int len2 = ft_strlen(s2);

    if (!s1 || !s2) /********** */
        return (NULL);

    res = malloc(len1 + len2 + 1); ////******** */
    if (!res)
        return (NULL);

    while (s1[i])
    {
        res[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        res[i] = s2[j];
        i++;
        j++;
    }
    res[i] = '\0'; /////****** */
    return (res);
}

char *join_str(char *res, char *buffer)
{
    char *tmp; //// char * not int *!!!

    tmp = ft_strjoin(res, buffer);
    if (!tmp)
    {
        free(res);
        res = NULL; ///******** */
        return (NULL);
    }
    free(res); ////******** */
    return (tmp);
}

char *read_line(int fd, char *res)
{
    char *buffer;
    int bytes_read = 1;

    if (!res)
    {
        res = malloc(1);
        res[0] = '\0';
    }
    if (!res)
        res = NULL;

    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
    {
        free(res);
        res = NULL;
        return (NULL);
    }
    while (bytes_read > 0)
    {
        bytes_read = read (fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(res);
            free(buffer);
            res = NULL;
            return (NULL);
        }
        buffer[bytes_read] = '\0';
        res = join_str(res, buffer);
        if (!res)
        {
            free(buffer);
            return (NULL);
        }
        if (strchr(buffer, '\n')) /******** */
            break ; /********** */
    }
    free(buffer); //////here we put it
    return (res); ///// here we put it 
}

char *set_line(char *buffer)
{
    char *line; /******** */
    int i = 0;
    int j = 0; /////******* */

    if  (!buffer[i]) /////if not while
        return (NULL);
    while (buffer[i] && buffer[i] != '\n')
        i++;

    line = malloc(i + 2);
    if (!line)
        return (NULL);
    
    while (buffer[i] && buffer[i] != '\n')
    {
        line[i] = buffer[i];
        i++;
    }
    if (buffer[i] == '\n')
        line[i] = '\n';
    return line;
}

char *set_next(char *buffer)
{
    char *line;
    int i = 0;
    int j = 0;

    if (!buffer)
        return (NULL);
    while (buffer[i] && buffer[i] != '\n')
        i++;
    if (buffer[i] == '\n')
        i++;


    if (!buffer[i])
    {
        free(buffer);
        buffer = NULL;
        return (NULL);
    }
    line = malloc (ft_strlen(buffer) - i + 1);
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
    return (line);
}

char *get_next_line(int fd)
{
    static char *buffer;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    buffer = read_line(fd, buffer); // fd, buffer
    if (!buffer)
        return (NULL);

    line = set_line(buffer);
    if (!line)
    {
        free(buffer);
        buffer = NULL;
        return (NULL);
    }
    buffer = set_next (buffer); // buffer = not line =
    return (buffer);
}