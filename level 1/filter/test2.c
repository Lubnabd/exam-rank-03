void ft_filter(char *buffer, char *target)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int t_len = strlen(target);

    while (buffer[i])/////////////
    {
        while (target[j] && (buffer[i + j] == target[j]))
            j++;
        if ( j == t_len) //// if not while
        {
            while  ( k < t_len) //// while not if 
            {
                write (1, "*", 1);
                k++;
            }
            i = i + t_len;
            continue;
        }
        else
        {
            write (1, &buffer[i], 1);
            i++;
        }
    }
}

int main (int argc, char **argc)
{
    char *buffer;
    char *res = NULL;
    char tmp[BUFFER_SIZE];
    ssize_t bytes_read;
    int total_read = 0; //// 0 not 1

    if (argc != 2 || argv[1][0] == '\0')
        return (NULL);
    while ((bytes_read = read(0, tmp, BUFFER_SIZE)) > 0)
    {
        buffer = realloc(res, (total_read + bytes_read + 1));///////////
        if (!buffer)
        {
            free(res);
            perror("realloc failed\n");
            return (NULL);
        }
        res = buffer; ///////////
        ft_memmove((res + total_read) , buffer, bytes_read); //// tmp not buffer
        total_read = total_read + bytes_read;
        res[total_read] = '\0'; //////////
    }
    if (bytes_read < 0)
    {
        free(res);
        retrun (NULL);
    }
    ft_filter(res, argv[1]);
    free(res);
}