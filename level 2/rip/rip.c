#include "rip.h"

int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

int good_closed(char *s, int n)
{
    int i = 0;
    int flag = 0;
    while ( i < n)
    {
        if (s[i] == '(')
            flag++;
        if (s[i] == ')')
            flag--;
        if (flag == -1) // more ) than (
            return 0;
    i++;
    }
    if (flag == 0)
        return 1;
    else
        return 0;
}

void check_rip(char *str, int n, int i, int *small, int lvl)
{
    char tmp;

    if (good_closed(str, n))
    {
        if (*small == -1 || lvl < *small)
            *small = lvl;
    }
    while (i < n)
    {
        tmp = str[i];
        str[i] = '_';
        lvl++;
        check_rip(str, n , i + 1, small, lvl);
        str[i] = tmp;
        lvl--;
        i++;
    }
}

void rip(char *str, int n, int i, int small, int lvl)
{
    char tmp;

    if (lvl > small)
        return ;
    if (good_closed(str, n) && lvl == small)
    {
        write (1, str, ft_strlen(str));
        write (1, " \n", 2);
        return ;
    }
    while ( i < n)
    {
        tmp = str[i];
        str[i] = '_';
        lvl++;
        rip(str, n, i + 1, small, lvl);
        str[i] = tmp;
        lvl--;
        i++;
    }
}

int main (int argc, char **argv)
{
    int small = -1; //signal that we haven’t found any valid combination yet.
    if (argc == 2)
    {
        check_rip(argv[1], ft_strlen(argv[1]), 0, &small, 0);
        rip(argv[1], ft_strlen(argv[1]), 0, small, 0);
    }
    else
        return 1;
}