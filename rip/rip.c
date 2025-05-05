#include <unistd.h>
#include <stdio.h>

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

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

void	check_rip(char *str, int n, int i, int *small, int lvl)
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
        write(1, str, ft_strlen(str));
		write(1, "\n", 1);
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
    check_rip(argv[1], ft_strlen(argv[1]),0, &small, 0);
    rip(argv[1], ft_strlen(argv[1]), 0, small, 0);
}

// small int indicates how many paranthesis must be removed at most