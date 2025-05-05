#include <unistd.h>
#include <stdio.h>

void ft_putstr(char *str)
{
    int i = 0;
    while (str[i])
        write(1, &str[i++], 1);
    write(1, "\n", 1);
}

int check_av(char *av)
{
    int i = 0;
    if (!av)
        return 0;
    while (av[i])
    {
        if (av[i] != '(' && av[i] != ')')
            return 0;
        i++;
    }
    return 1;
}

int is_matching(char *str)
{
    int count = 0;
    int i = 0;
    while (str[i])
    {
        if (str[i] == '(')
            count++;
        else if (str[i] == ')')
        {
            count--;
            if (count < 0)
                return 0;
        }
        i++;
    }
    if(count == 0)
    {
        ft_putstr(str);
        return 1;
    }
    return (0);
}

int main(int ac, char **av)
{
    if (ac != 2 || !check_av(av[1]) || !is_matching(av[1]))
    {
        ft_putstr("error");
        return 1;
    }

    return 0;
}