#include <unistd.h>
#include <string.h>
#include <stdio.h>

int good_closed(char *str, int n)
{
    int i = 0;
    int flag = 0;

    while (i < n)
    {
        if (str[i] == '(')
            flag++;
        if (str[i] == ')')
            flag--;
        if (flag == -1)
            return 0;
        i++;
    }
    if (flag == 0)
        return 1;
    return 0;
}

void check_rip(char *str, int n, int i, int *small, int lvl)
{
    char tmp;
    if (good_closed(str, n))
    {
        if (*small == -1)
            *small = lvl;
        else if (lvl < *small)
            *small = lvl;
    }
    while (i < n)
    {
        tmp = str[i];
        str[i] = '_';
        lvl++;
        check_rip(str, n, i + 1, small, lvl);
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
    if (good_closed(str, n) &&  lvl == small)
    {
        printf("%s\n", str);
        return ;
    }
    while (i < n)
    {
        tmp = str[i];
        lvl++;
        str[i] = '_';
        rip(str, n, i + 1, small, lvl);
        str[i] = tmp;
        lvl--;
        i++;
    }
}

int main(int argc, char **argv)
{
    int small = -1;
    if (argc != 2)
        return 1;
    check_rip(argv[1], strlen(argv[1]),0, &small, 0);
    rip(argv[1], strlen(argv[1]), 0, small, 0);
}