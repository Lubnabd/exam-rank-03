#include "permutations.h"
// should i check args here?
int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

int ft_isalpha(int c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

void ft_swap(char *a, char *b)
{
    char t;

    t = *a;
    *a = *b;
    *b = t;
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

char *order(char *s)
{
    int i;
    int swap;
    int len = ft_strlen(s);

    swap = 1;
    while (swap)
    {
        swap = 0; // assume nothing will need swapping
        i = 0;
        while (i < len - 1)
        {
            if (s[i] > s[i + 1])
            {
                ft_swap(&s[i], &s[i + 1]);
                swap = 1; // A swap happened so we need another pass
            }
            i++;
        }
    }
    return (s);
}

void permutations(char *s, char *res, int pos)
{
    
    int i = 0;
    if (res && (ft_strlen(res) == ft_strlen(s)))
    {
        write (1, res, ft_strlen(res));
        write (1, "\n", 1);
    }
    while ( i < ft_strlen(s))
    {
        if (!ft_strchr(res, s[i])) // check if character is already used
        {
            res[pos] = s[i];
            permutations(s, res, pos + 1);
            res[pos] = '\0';
        }
        i++;
    }
}

int main (int argc , char **argv)
{
    char *res;
    char *s;

    if (argc == 2)
    {
        if (ft_strlen(argv[1]) == 0 || (argv[1][0] == ' ' && !argv[1][1]))
            return (0);
        int i = 0;
        while (argv[1][i])
        {
            if (!ft_isalpha(argv[1][i]))
                return 0;
            i++;
        }
        res = calloc(ft_strlen(argv[1]), 1);
        if (!res)
            return (1);
        s = order(argv[1]);
        permutations(s, res, 0);
        free(res);
    }
    else
        return 1;
}
