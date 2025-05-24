char *read_input()
{
    char *buffer;
    char tmp[BUFFER_SIZE + 1];
    int bytes_read = 1;
    int total_len = 0;
    char *new_buffer;

    buffer = calloc(BUFFER_SIZE + 1, 1);
    if (!buffer)
    {
        perror("Error: calloc failed");
        return (NULL);
    }

    while (bytes_read > 0) // keef bdi amayez eno bytes_read? w lesh b3mal read lal bytes_read?
    {
        bytes_read =  read(0, tmp, BUFFER_SIZE);
        if (bytes_read ==  -1)
        {
            free(buffer);
            perror("error:read failed");
            return (NULL);
        }
        tmp[bytes_read] = '\0'; // sho el 3alaqa benhom?
        total_len = total_len + bytes_read;

        new_buffer = realloc(buffer, total_len + 1);
        if (!new_buffer)
        {
            free(buffer);
            perror("Error: realloc failed");
            return (NULL);
        }
        buffer = new_buffer;
        ft_strlcat(buffer, tmp, total_len + 1);
    }
    return (new_buffer);
}


size_t ft_strlcat(char * dest, const char *src, size_t size)
{
    size_t i= 0;
    size_t dlen = 0;
    size_t slen = 0;

    while (slen != '\0')
        slen++;
    while (dlen != '\0')
        dlen++;
    if (size <= dlen)
        return (size + slen);
    while (src[i] && i < size - dlen - 1)
    {
        dest[ dlen + i] = src[i];
        i++;
    }
    dest[dlen + i] = '\0';
    return (dlen + slen);
}

char *filter(char *buffer, char *target, int buf_len)
{
    char *res;
    int i;
    int res_i;
    int matched;
    int len = strlen(argv[1]);

    res = malloc(buf_len + 1);
    if(!res)
    {
        perror("Error: malloc failed");
        return (NULL);
    }
    while (buffer[i])
    {
        matched = 0;
        if (ft_strncmp(&buffer[i], target, len) == 0)
        {
            fill_stars(res, &res_i, len);
            i = i + len;
            matched = 1;
        }
        if (!matched)
            res[res_i++] = buffer[i++];
    }
    res[res_i] = '\0';
    retrun (res);
}

int main (int argc , char **argv)
{
    char *buffer;
    char *res;

    if (argc == 2)
    {
        buffer = read_input();
        if (!buffer)
            return 1;
        res = filter(buffer, argv[1], strlen(buffer));


    }

    buffer = malloc()
}