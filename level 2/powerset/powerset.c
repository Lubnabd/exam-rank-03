#include "powerset.h"

void print_subset(int *subset, int size)
{
    int i = 0;
    if (size == 0)
        return ;
    while (i < size)
    {
        if ( i == size - 1)
            printf("%d", subset[i]);
        else
            printf("%d ", subset[i]);
        i++;
    }
    printf("\n");
}

void backtrack(int *set, int *subset, int size, int index, int sub_size, int current_sum, int target, int *found)
{
    if (index == size)
    {
        if (current_sum == target)
        {
            print_subset(subset, sub_size);
            *found = 1;
        }
        return ;
    }
    backtrack(set, subset, size, index + 1, sub_size, current_sum, target, found);
    subset[sub_size] = set[index];
    backtrack(set, subset, size, index + 1, sub_size + 1, current_sum + set[index], target, found);
}

int main (int argc , char **argv)
{
    int set[argc - 2]; // after we do the atoi
    int subset[argc - 2];
    int i = 0;
    int j = 2;
    int size = argc - 2;
    int target = atoi(argv[1]);
    int found = 0;

   if (argc > 2)
    {
        while ( j < argc)
        {
            set[i] = atoi(argv[j]);
            i++;
            j++;
        }
        backtrack(set, subset, size, 0 , 0, 0, target, &found);
        if (!found)
            printf("\n");
    }
    else
        return 1;
}