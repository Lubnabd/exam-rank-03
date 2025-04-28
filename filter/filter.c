#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

//ft_stncmp

void	fill_stars(char *res, int *res_i, int len)
{
	int	j;

	j = 0;
	while (j < len)
	{
		res[*res_i] = '*';
		(*res_i)++;
		j++;
	}
}


char	*filter(char *buffer, char *target, int buf_len)
{
	char	*res;
	int		i = 0;
	int		res_i = 0;
	int		matched;
	int		t_len = ft_strlen(target);

	res = malloc(buf_len + 1);
	if (!res)
		return (NULL);

	while (buffer[i])
	{
		matched = 0;

		// Check for target match
		if (strncmp(&buffer[i], target, t_len) == 0)
		{
			fill_stars(res, &res_i, t_len);
			i += t_len;
			matched = 1;
		}
		if (!matched)
			res[res_i++] = buffer[i++];
	}
	res[res_i] = '\0';
	return (res);
}

int	main(int argc, char **argv)
{
	int		num_bytes;
	char	buffer[9999];
	char	*result;

	if (argc == 2)
	{
		num_bytes = read(0, buffer, 9999);
		result = filter(buffer, argv[1], num_bytes);
		if (!result)
			perror("allcoation failed\n");
		write(1, result, num_bytes);
		free (result);
	}
}

/*void	fill_stars(char *res, int *res_i, int len)
{
	int	j = 0;
	while (j < len)
	{
		res[*res_i] = '*';
		(*res_i)++;
		j++;
	}
}

char	*filter(char *buffer, char *target, int buf_len)
{
	char	*res;
	int		res_i = 0;
	char	*curr = buffer;
	char	*match;
	int		t_len = strlen(target);

	res = malloc(buf_len + 1);
	if (!res)
		return (NULL);

	while ((match = memmem(curr, buffer + buf_len - curr, target, t_len)))
	{
		int prefix_len = match - curr;
		memmove(&res[res_i], curr, prefix_len);
		res_i += prefix_len;
		fill_stars(res, &res_i, t_len);
		curr = match + t_len;
	}
	// Copy the rest
	memmove(&res[res_i], curr, buffer + buf_len - curr);
	res_i += buffer + buf_len - curr;
	res[res_i] = '\0';
	return (res);
}

int	main(int argc, char **argv)
{
	int		num_bytes;
	char	buffer[9999];
	char	*result;

	if (argc == 2)
	{
		num_bytes = read(0, buffer, 9999);
		result = filter(buffer, argv[1], num_bytes);
		if (!result)
			perror("allocation failed\n");
		write(1, result, strlen(result));
		free(result);
	}
}*/