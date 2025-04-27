#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10

void	ft_strlcat(char *dst, char *src) {
	int	i = 0;
	int	n = strlen(dst);

	while(src[i]) {
		dst[n] = src[i];
		i++;
		n++;
	}
	dst[n] = '\0';
}

char *read_str(void) {
	char tmp[BUFFER_SIZE + 1];
	char *buf;
	char *new_buf;
	int bytes_read = 1;
	int total_len = 0;

	buf = calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (perror("Error"), NULL);
	while ((bytes_read = read(0, tmp, BUFFER_SIZE)) > 0) {
		tmp[bytes_read] = '\0';
		total_len += bytes_read;
		new_buf = realloc(buf, total_len + 1);
		if (!new_buf) {
			free(buf);
			return (perror("Error"), NULL);
		}
		buf = new_buf;
		ft_strlcat(buf, tmp);
	}
	return(new_buf);
}

char *search_and_replace(char *str, char *needle) {
	int i = 0;
	int j = 0;
	char *result;
	int r = 0;

	if(!str || !needle || !*needle)
		return (NULL);
	result = malloc(sizeof(char) * (strlen(str) + 1));
	if (!result)
		return (perror("Error"), NULL);
	while (str[i]) {
		j = 0;
		while(needle[j] && str[i + j] == needle[j])
			j++;
		if (!needle[j]) {
			while (j > 0) {
				result[r] = '*';
				j--;
				r++;
			}
			i+= strlen(needle);
		}
		else {
			result[r] = str[i];
			i++;
			r++;
		}
	}
	result[r] = '\0';
	free(str);
	return (result);
}

int main(int ac, char **av)
{
	char *input;
	char *result;

	if (ac < 2)
		return (1);
	input = read_str();
	if (!input)
		return (1);
	result = search_and_replace(input, av[1]);
	if (!result)
		return (1);
	printf("%s\n", result);
	free(result);
	return (0);
}
