#define _GNU_SOURCE
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void ft_filter(char *buffer, const char *target)
{
    int i = 0;
    int t_len = strlen(target);
    int j;
    int k;

    while (buffer[i])
    {
        j = 0;
        while (target[j] && (buffer[i + j] == target[j]))
            j++;
        if (j == t_len)
        {
            k = 0;
            while (k < t_len)
            {
                write(1, "*", 1);
                k++;
            }
            i = i + t_len;
            continue;
        }
        else
        {
            write(1, &buffer[i], 1);
            i++;
        }
    }
}

int main(int argc, char *argv[])
{
    char buffer[BUFFER_SIZE];
    char *input = NULL;
    char *temp;
    int total_read = 0;
    ssize_t bytes;

    if (argc != 2 && argv[1][0] == '\0')
        return 1;

    while ((bytes = read(0, buffer, BUFFER_SIZE)) > 0)
    {
        temp = realloc(input, total_read + bytes + 1);
        if (!temp)
        {
            free(input);
            perror("realloc");
            return (1);
        }
        input = temp;
        memmove(input + total_read, buffer, bytes);
        total_read = total_read + bytes;
        input[total_read] = '\0';
    }

    if (bytes < 0)
    {
        perror("read");
        free(input);
        return (1);
    }

    ft_filter(input, argv[1]);
    free(input);
    return (0);
}
