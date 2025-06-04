// test valgrind
#include <unistd.h> // read
#include <errno.h> // for perror
#include <stdio.h> // printf
#include <stdlib.h> // malloc, calloc, realloc, free
#include <string.h> // for strlen

# define BUFFER_SIZE 42

size_t ft_strlcat(char *dst, const char *src, size_t size)
{
    size_t i = 0;
    size_t dlen = 0;
    size_t slen = 0;

    while (src[slen])
        slen++;
    while (dst[dlen])
        dlen++;

    // copy loop //
    while (src[i] && i < size - dlen - 1) //Only copy as many characters as will fit safely in the dst buffer
    {
        dst[dlen + i] = src[i];
        i++;
    }
    dst[dlen + i] = '\0';
    return (dlen + slen);
}

char *read_line()
{
    char *buffer;
    char *new_buf;
    char tmp[BUFFER_SIZE + 1];
    int total_len = 0;
    int bytes_read = 1;

    buffer = calloc(BUFFER_SIZE + 1, 1); // focus here
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
        new_buf = realloc(buffer, total_len + 1);
        if (!new_buf)
        {
            free(buffer);
            perror("realloc failed\n");
            return (NULL);
        }
        buffer = new_buf;
    // buffer is the dest, tmp is the src, and total_len + 1 is the size
    // It concatenates (tmp) to the end of (buffer) safely, not overflowing
        ft_strlcat(buffer, tmp, total_len + 1);
    }
    return (new_buf);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i = 0;
    size_t j;

    while ( i < n && (s1[i] || s2[i]))
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
        (*res_i)++; // focus here
        j++;
    }
}

char *filter(char *buffer, char *target, int buf_len)
{
    char *res;
    int matched; //flag to tell if we matched target
	int i = 0;
	int j = 0; // if not set to 0 you get bus error
	int t_len = strlen (target);

    res = malloc(buf_len + 1);
    if (!res)
    {
        //free(buffer); ??
        return (NULL);
    }
    while (buffer[i])
    {
        matched = 0; // **
        if (ft_strncmp(&buffer[i], target, t_len) == 0) //focus here
        {
            fill_stars(res, &j, buf_len, t_len);
            i = i + t_len;
            matched = 1;
        }
        if (!matched)
            res[j++] = buffer[i++];
    }
    res[j] = '\0';
    return (res);
}

int main (int argc, char **argv)
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
            //why not free buffer here?
            perror("allocation failed");
		    return (1);
        }
        printf("%s", res);
        free(res);
        free(buffer);
    }
    else
        return 1;
}

// when testing the code without echo you can see the result after ctrl + d //