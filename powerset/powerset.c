#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	print_subset(int *subset, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (i == size - 1)
			printf("%d", subset[i]);
		else
			printf("%d ", subset[i]);
		i++;
	}
	printf("\n");
}

void	backtrack(int *set, int size, int index,
				int *subset, int subset_size,
				int current_sum, int target)
{
	if (index == size)
	{
		if (current_sum == target)
			print_subset(subset, subset_size);
		return ; 
	}
	backtrack(set, size, index + 1, subset, subset_size, current_sum, target);
	subset[subset_size] = set[index];
	backtrack(set, size, index + 1, subset, subset_size + 1, current_sum + set[index], target);

}

int	main(int argc, char **argv)
{
	int	set[argc - 2];
	int	subset[argc - 2];
	int i = 0;
	int j = 2;
	int	size = argc - 2;
	int	target = atoi(argv[1]);

	if (argc < 3)
		return (1);

	while (j < argc)
	{
		set[i] = atoi(argv[j]);
		i++;
		j++;
	}
	backtrack(set, size, 0, subset, 0, 0, target);
}
