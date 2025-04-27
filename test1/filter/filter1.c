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
/*#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

void	print_error(void)
{
	perror("Error");
	exit(1);
}
char	*ft_strdup(char *s)
{
	int		i;
	char	*cpy;

	i = 0;
	if (!s)
		return (NULL);
	cpy = malloc(sizeof(char) * (strlen(s) + 1));
	if (!cpy)
		return (NULL);
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	char	*dest;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	dest = malloc(strlen(s1) + strlen(s2) + 1);
	if (!dest)
		return (NULL);
	result = dest;
	while (*s1)
		*dest++ = *s1++;
	while (*s2)
		*dest++ = *s2++;
	*dest = '\0';
	return (result);
}

void	ft_check_replace(char **str, char *to_replace)
{
	if (!str || !*str || !to_replace)
		return;
	char	*new_str = malloc(strlen(*str) + 1);
	size_t	len = strlen(to_replace);
	size_t	src_len = strlen(*str);
	if (!new_str)
	{
		free(*str);
		print_error();
	}
	char *src = *str;
	char *dst = new_str;
	while (*src)
	{
		size_t i = 0;
		while (to_replace[i] && src[i] == to_replace[i])
			i++;
		if (i == len)
		{
			for (size_t j = 0; j < len; j++)
				*dst++ = '*';
			src += len;
		}
		else
			*dst++ = *src++;
	}
	*dst = '\0';
	free(*str);
	*str = new_str;
}

int	main(int ac, char **av)
{
	if (ac != 2 || !(av[1][0]))
		return (1);

	char	*dest;
	char	*str = NULL;
	dest = malloc((size_t)BUFFER_SIZE + 1);
	if (!dest)
		print_error();
	ssize_t line_b = 1;
	while (line_b > 0)
	{
		line_b = read(0, dest, BUFFER_SIZE);
		if (line_b == -1)
		{
			free(dest);
			free(str);
			print_error();
		}
		dest[line_b] = '\0';
		char *tmp = ft_strjoin(str, dest);
		if (!tmp)
		{
			free(dest);
			free(str);
			print_error();
		}
		free(str);
		str = tmp;
	}
	free(dest);
	ft_check_replace(&str, av[1]);
	printf("%s", str);
	free(str);
	return (0);
}*/