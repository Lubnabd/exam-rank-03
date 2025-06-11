#ifndef POWERSET_H
# define POWERSET_H

# include <stdio.h>
# include <stdlib.h>

void	print_subset(int *subset, int size);
void    backtrack(int *set,  int *subset, int size, int index,
                int sub_size, int current_sum, int target, int *found);

#endif
