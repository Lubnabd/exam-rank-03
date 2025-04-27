#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int ft_atoi(char *str)
{
    int i = 0;
    int res = 0;
    int sig = 1;

    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sig *= -1;
        i++;
    }
    while (str[i] && (str[i] >= '0' && str[i] <= '9'))
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return (res * sig);
}

int check_int(char **str, int ac)
{
    int j = 1;
    while (j < ac)
    {
        int i = 0;
        if (str[j][i] == '-' || str[j][i] == '+')
            i++;
        while (str[j][i])
        {
            if (str[j][i] < '0' || str[j][i] > '9')
                return 0;
            i++;
        }
        j++;
    }
    return 1;
}

void print_set(int *tab, int size)
{
    int i = 0;
    while (i < size)
    {
        printf("%d ", tab[i]);
        i++;
    }
    printf("\n");
}

void powerset(int *arr, int n, int target)
{
    int max = 1 << n; // 2^n subsets
    int mask = 1;

    while (mask < max)
    {
        int i = 0;
        int sum = 0;
        int *set = malloc(sizeof(int) * n);
        int idx = 0;

        while (i < n)
        {
            if ((mask >> i) & 1)
            {
                sum += arr[i];
                set[idx] = arr[i];
                idx++;
            }
            i++;
        }

        if (sum == target)
            print_set(set, idx);

        free(set);
        mask++;
    }
}

int main(int ac, char **av)
{
    if (ac < 3 || !check_int(av, ac))
        return 1;

    int target = ft_atoi(av[1]);
    int n = ac - 2;

    int *arr = malloc(sizeof(int) * n);
    int i = 0;
    while (i < n)
    {
        arr[i] = ft_atoi(av[i + 2]);
        i++;
    }

    powerset(arr, n, target);
    free(arr);
    return 0;
}