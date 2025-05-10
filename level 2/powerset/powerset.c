#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	print_subset(int *subset, int size)
{
    int i = 0;
    while ( i < size)
    {
        if (i == size - 1) //???
            printf("%d", subset[i]);
        else
            printf("%d ", subset[i]);
        i++;
    }
    printf("\n");
}

void backtrack(int *set,  int *subset, int size, int index,
    int subset_size, int current_sum, int target)
{
    if (index == size) // why not index + 1 == size? // did we consider subsetsize 1 or 0? because current sum is 0
    {
        if (current_sum == target) //? // 1 2 3 target is 5??
            print_subset(subset, subset_size);
        return ;
    }
    backtrack(set, subset, size, index + 1, subset_size, current_sum, target); // from line 28 to 30?
    subset[subset_size] = set[index];
    backtrack(set, subset, size, index + 1, subset_size + 1, current_sum + set[index], target);
}

int main (int argc, char ** argv)
{
    int set[argc - 2]; // how would the program know that the first two elements not the last?
    int subset[argc - 2];
    int i = 0;
    int j = 2; //argv? no
    int size = argc - 2; // whats the point of having three int that equals the same?
    int target = atoi(argv[1]);

    if (argc > 2)
    {
        while (j < argc)
        {
            set[i] = atoi(argv[j]);
            i++;
            j++;
        }
        backtrack(set, subset , size, 0, 0, 0, target);
    }
}