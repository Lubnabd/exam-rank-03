# include <stdio.h>
# include <stdlib.h>

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

void backtrack(int *set, int *subset, int size,int sub_size, int index, int current_sum, int target, int *found)
{
    if (index == size) // 0 because goes from 0 to size - 1
    {
        if (current_sum == target)
        {
            print_subset(subset, sub_size);
            *found = 1;
        }
        return ;
    }
    backtrack(set, subset, size, sub_size, index + 1,  current_sum, target, found);
    subset[sub_size] = set[index];  // Add the number to the current subset
    backtrack(set, subset, size, sub_size + 1, index + 1, current_sum + set[index], target, found);
    // You're adding an element to the subset → sub_size increases
}

int check_args(int argc, char **argv)
{
    int i = 1;
    while (i < argc)
    {
        int j = 0;
        if (argv[i][j] == '+' || argv[i][j] == '-')
            j++;
        while (argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return 0;
            j++;
        }
        i++;
    }
    return 1;
}

int main (int argc , char **argv)
{
    if (argc == 1)
        return 1;
    if (!check_args(argc, argv))
        return 1;
    int set[argc - 2];
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
            set[i] = atoi(argv[j]); // Fill the set array with numbers from the command line
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