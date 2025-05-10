#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 10

size_t ft_strlcat(char *dest, const char *src, size_t size)
{
    size_t i = 0;
    size_t dlen = 0;
    size_t slen = 0;

    while (src[slen] != '\0')
        slen++;
    while (dest[dlen] != '\0' && dlen < size) // why didn't we check the same in line 14? //because we're just measuring how long src
        dlen++;
    if (size <= dlen)
        return (size + slen);
    while (src[i] != '\0' && i < size - dlen - 1)
    {
        dest[dlen + 1] = src[i];
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

    buffer = calloc(BUFFER_SIZE + 1, 1);
    if (!buffer)
    {
        perror("Error: calloc failed\n");
        return (NULL);
    }
    while (bytes_read > 0)
    {
        bytes_read = read(0, tmp, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(buffer);
            perror ("Erro: read failed\n");
            return (NULL);
        }
        tmp[bytes_read] = '\0';
        total_len = total_len + bytes_read;
        new_buffer = realloc(buffer, total_len + 1); //??
        if (!new_buffer)
        {
            free(buffer);
            perror("Error: realloc failed\n");
            return (NULL);
        }
        buffer = new_buffer;
        ft_strlcat(buffer, tmp, total_len + 1);
    }
    return (new_buffer);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t t;
    size_t i;

    i = 0;
    while ( i < n && (s1[i] != '\0' || s2[i] != '\0'))
    {
        t = (unsigned char)s1[i] - (unsigned char)s2[i];
        if (t == 0)
            i++;
        else
            return (t);
    }
    return (0);
}

void fill_stars(char *res, int *res_i, int len)
{
    int j = 0;
    while (j < len)
    {
        res[*res_i] = '*';
        (*res_i)++;
        j++;
    }
    //??
}

char *filter(char *buffer, char *target, int buf_len)
{
    char *res;
    int i =0;
    int res_i = 0;
    int matched;
    int t_len = strlen(target);

    res = malloc(buf_len + 1);
    if (!res)
        return (NULL);
    while (buffer[i])
    {
        matched = 0; // can i do this on line 100? //You need to reset it on each iteration.
        if (ft_strncmp(&buffer[i], target, t_len) == 0)
        {
            fill_stars(res, &res_i, t_len);
            i = i + t_len;
            matched = 1;
        }
        if (!matched)
            res[res_i++] = buffer[i++];
        }
        res[res_i] = '\0';
        return (res);
}

int main (int argc , char **argv)
{
    char *res;
    char *buffer;

    if (argc == 2) // should't we check || argv[1][0] != '\0' ?
    {
        buffer = read_input();
        if (!buffer)
            return (1);
        res = filter(buffer, argv[1], strlen(buffer));
        if (!res)
        {
            perror("Error:allocation failed\n");
            return (1);
        }
        printf("%s", res);
        free (res);
        free (buffer);
    }
    else
        return 1;
}