#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int ft_strlen(char *s)
{
    int i = 0;

    while (s[i])
        i++;
    return (i);
}

void ft_swap(char *a, char *b)
{
    char tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

char *order(char *s)
{
    int i = 0;
    int len = ft_strlen(s);
    int swap;

    while (s[i] && s[i +1])
    {
        if (s[i] < s[i + 1])
            i++;
        else
            break;
    }
    if ((i + 1) == len)
        return (s);
    swap = 1;
    while (swap)
    {
        swap = 0;
        i = 0;
        while (s[i] && s[i + 1])
        {
            if (s[i] > s[i + 1])
            {
                ft_swap(&s[i], &s[i + 1]);
                swap = 1;
            }
            i++;
        }
    }
    return (s);
}

int ft_strchr(const char *s, char c)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == c)
            return (1);
        i++;
    }
    return (0);
}

void permutations(char *s, char *result, int pos)
{
    int i = 0;
    if (result && (ft_strlen(result) == ft_strlen(s)))
    {
        write (1, result, ft_strlen(result));
        write (1, "\n", 1);
    }
    while ( i < ft_strlen(s))
    {
        if (!ft_strchr(result, s[i]))
        {
            result[pos] = s[i];
            permutations (s, result, pos + 1);
            result[pos] = '\0';
        }
        i++;
    }
}

int main (int argc , char ** argv)
{
    char *s;
    char *res;

    if (argc == 2)
    {
        res = calloc(ft_strlen(argv[1]), 1);
        s = order(argv[1]);
        permutations(s, res, 0);
        free(res);
    }
    else
        return 1;
}