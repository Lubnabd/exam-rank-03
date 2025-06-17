#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define BUFFER_SIZE 42

size_t ft_strlcat(char *dest, char *src, size_t size)
{
    size_t i = 0;
    size_t slen = 0;
    size_t dlen = 0;

    while (src[slen])
        slen++;
    while (dest[dlen])
        dlen++;
// copy loop //
    while (src[i] && (dlen + i + 1) < size) //Only copy as many characters as will fit safely in the dst buffer
    {
        dest[dlen + i] = src[i];
        i++; 
    }
    dest[dlen + i] = '\0';
    return (dlen + slen);
}

char *read_line()
{
    char *buffer;
    char *res;
    int total_len = 0;
    int bytes_read = 1;
    char tmp[BUFFER_SIZE + 1];

    buffer = calloc(BUFFER_SIZE + 1 , 1);
    if (!buffer)
    {
        perror("calloc failed\n");
        return (NULL);
    }
    while(bytes_read > 0)
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
        res = realloc(buffer, total_len + 1);
        if (!res)
        {
            free(buffer);
            perror("realloc failed\n");
            return (NULL);
        }
        buffer = res;
    // buffer is the dest, tmp is the src, and total_len + 1 is the size
        ft_strlcat(buffer, tmp, total_len + 1);
    }
        return (res);
}

int ft_strncmp(const char *s1, const char *s2, size_t size)
{
    size_t i = 0;
    size_t j;

    while ( i < size && (s1[i] || s2[i]))
    {
        j = (unsigned char)s1[i] - (unsigned char)s2[i];
        if (j == 0)
            i++;
        else
            return j; // Return the actual difference between the differing characters
    }
    return 0;
}

void fill_stars(char *res, int *res_i, int max_len, int len)
{
    int j = 0;
    while (j < len && *res_i < max_len)
    {
        res[*res_i] = '*';
        (*res_i)++; 
        j++;
    }
}

char *filter(char *buffer, char *target, int len)
{
    char *res;
    int matched; // flag to tell if we matched target
    int i = 0;
    int j = 0; // if not set to 0 you get bus error
    int t_len = strlen(target);

    res = malloc(len + 1);
    if (!res)
    {
        perror("malloc failed\n");
        return (NULL);
    }
    while (buffer[i])
    {
        matched = 0;
        if (ft_strncmp(&buffer[i], target, t_len) == 0) 
        {
            fill_stars(res, &j, len, t_len); 
            i = i + t_len; 
            matched = 1; 
        }
        if (!matched)
            res[j++] = buffer[i++];
    }
    res[j] = '\0';
    return (res);
}

int main (int argc , char **argv)
{
    char *buffer;
    char *res;

    if (argc == 2 && argv[1][0])
    {
        buffer = read_line();
        if (!buffer)
            return 1;
        res = filter(buffer, argv[1], strlen(buffer));
        if (!res)
        {
            free(buffer);
            perror("allocation failed\n");
            return 1;
        }
        printf("%s", res);
        free(res);
        free(buffer);
    }
    else
        return 1;
}

// when testing the code without echo you can see the result after ctrl + d //