#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void ft_swap(char *c1, char *c2)
{
    char tmp = *c1;
    *c1 = *c2;
    *c2 = tmp;
}


int ft_strlen(char *str)
{
    int i = 0;
    while(str[i])
        i++;
    return i;
}

int check_double(char *str)
{
    int i = 0;
    while(str[i])
    {
        int j = i + 1;
        while(str[j])
        {
            if(str[i] == str[j] && str[j])
                return 0;
            j++;
        }
        i++;
    }
    return 1;
}

void    str_sorted(char *str)
{
    int i = 0;
    while(str[i])
    {
        int j = i + 1;
        while(str[j])
        {
            if(str[i] > str[j])
                ft_swap(&str[i], &str[j]);
            j++;
        }
        i++;
    }
}

int ft_permutition(char *str, int len)
{
    int i = len - 2;
    while(i >= 0 && str[i + 1] < str[i])
        i--;
    if(i < 0)
        return 0;
    int j = len - 1;
    while(str[j] < str[i])
        j--;
    ft_swap(&str[i], &str[j]);
    int s = i + 1;
    int e = len - 1;
    while(s < e)
    {
        ft_swap(&str[s], &str[e]);
        s++;
        e--;
    }
    return 1;
}

int main(int ac, char **av)
{
    if(ac != 2)
        return 0;
    int i = 0;
    int len = ft_strlen(av[1]);
    char *ptr = malloc(len + 1);
    if (!ptr)
        return 0;
    while(av[1][i])
    {
        ptr[i] = av[1][i];
        i++;
    }
    ptr[i] = '\0';
    if (!check_double(ptr))
        return 0;
    str_sorted(ptr);
    printf("%s\n", ptr);
    while(ft_permutition(ptr, len))
        printf("%s\n", ptr);

}