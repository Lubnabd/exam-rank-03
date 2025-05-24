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

    while (slen != '\0')
        slen++;
    while (dlen != '\0')
        dlen++;

    if (size <= dlen) //??
        return (size + slen); // ??
    while (src[i] && i < size - dlen - 1) //??
    {
        dest[dlen + i] = src[i]; //?? and why i?
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
    int bytes_read = 1; //??
    int total_len = 0;

    buffer = calloc(BUFFER_SIZE + 1, 1);
    if (!buffer)
    {
        perror("Error: calloc failed\n");
        return (NULL);
    }

    while (bytes_read > 0) // why do i check bytes read ?
    {
        bytes_read = read(0, tmp, BUFFER_SIZE); // why buffer size?
        if (bytes_read == -1)
        {
            free(buffer); // why do i free the buffer here? not before line 12?
            perror ("Error: read failed\n");
            return (NULL);
        }
        tmp[bytes_read] = '\0';
        total_len = total_len + bytes_read;

        new_buffer = realloc(buffer, total_len + 1);
        if (!new_buffer)
        {
            free(buffer); // why?
            perror("Error: realloc failed\n");
            return (NULL);
        }
        buffer = new_buffer;
        ft_strlcat(buffer, tmp, total_len + 1); // what does this do?
    }
        return (new_buffer);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;
    size_t j;

    i = 0;
    while (i < n && (s1[i] || s2[i]))
    {
        j = (unsigned char)s1[i] - (unsigned char)s2[i];
        if (j == 0)
            i++;
        else
            return (j);
    }
    return 0;
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
}

char *filter(char *buffer, char *target, int buf_len)
{
    char *res;
    int matched;
    int i =0;
    int res_i = 0;
    int t_len = strlen(target);

    res = malloc(buf_len + 1);
    if (!res)
    {
        perror("Error: malloc failed\n");
        return (NULL);
    }

    while (buffer[i])
    {
        matched = 0;
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
        buffer = read_input(); // why didn't i check before line 130 if argv[1] != '\0'
        if (!buffer) // why did i do the protection here?
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