#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void	permutations(char *s, char *result, int pos)
{
	int	i;

	i = 0;
	if (result && (strlen(result) == strlen(s)))
		printf("%s\n", result);
	while ((size_t)i < strlen(s))
	{
		if (!strchr(result, s[i]))
		{
			result[pos] = s[i];
			permutations(s, result, pos + 1);
			result[pos] = '\0';
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	permutations(av[1], calloc(strlen(av[1]), 1), 0);
}