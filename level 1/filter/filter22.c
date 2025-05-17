size_t ft_strlcat(char *target, const char *src , size_t size)
{
    size_t i = 0;
    size_t dlen = 0;
    size_t slen = 0;

    while (src[slen] != '\0')
        slen++;
    while (dlen[dlen] != '\0' && dlen < size)
        dlen++;
    if (size <= dlen)
        return (size + slen);
    while (src[i] != '\0' && i < size - dlen - 1)
    {
        dest[dlen + 1] = src[i]; //??
        i++;
    }
    dest[dlen + i] = '\0';
    return (dlen + slen);
}





char *read_input()
{
    char tmp[BUFFER_SIZE + 1];
    char *buffer;
    char *new_buffer;
    int bytes_read = 1;
    int total_len = 0;

    buffer = calloc(BUFFER_SIZE + 1, 1); // make sure to read what calloc takes
    if (!buffer)
    {
        perror("calloc failed\n");
        return (NULL);
    }
    while (bytes_read > 0)
    {
        bytes_read = read(0, tmp, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(buffer);
            perror("read failed\n");
            return (NULL);
        }
        tmp[bytes_read] = '\0';
        total_len = total_len + bytes_read;
        new_buffer = realloc(buffer, total_len + 1);

        if (!new_buffer)
        {
            free(buffer);
            perror("realloc failed\n");
            return (NULL);
        }
        buffer = new_buffer;
        ft_strlcat(buffer, tmp, total_len + 1);
    }
    return (new_buffer);
}


int main (int argc , char **argv)
{
    char *buffer;
    char *res;

    if (argc == 2)
    {
        
        buffer = read_input;
    }
    else
        return 0;
}