#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_strchr(char *s, int c)
{
	int i = 0;
	if (!s)
		return NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			return s + i;
		i++;
	}
	return NULL;
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (!dest || !src)
		return NULL;
	for (size_t i = 0; i < n; i++)
		((char *)dest)[i] = ((char *)src)[i];
	return dest;
}

size_t	ft_strlen(char *s)
{
	size_t ret = 0;
	while (s && *s++)
		ret++;
	return ret;
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1 = ft_strlen(*s1);
	char *tmp = malloc(size1 + size2 + 1);
	if (!tmp)
	{
		free(*s1);
		*s1 = NULL;
		return 0;
	}
	if (*s1)
		ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return 1;
}

int	str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (!dest || !src)
		return NULL;
	//if (dest == src || n == 0)
		//return dest;
	if (dest < src)
		return ft_memcpy(dest, src, n);
	while (n--)
		((char *)dest)[n] = ((char *)src)[n];
	return dest;
}

char	*get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	char *tmp;
	ssize_t read_ret;
	read_ret = -1;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;

	tmp = ft_strchr(b, '\n');
	while (!tmp)
	{
		if (*b && !str_append_str(&ret, b))
			return NULL;

		read_ret = read(fd, b, BUFFER_SIZE);

		if (read_ret < 0)
		{
			b[0] = 0;
			if (ret)
				free(ret);
			return NULL;
		}
		else if (read_ret == 0)
		{
			if (ret && *ret)
			{
				b[0] = 0;
				return ret;
			}
			free(ret);
			return NULL;
		}
		b[read_ret] = 0;
		tmp = ft_strchr(b, '\n');
	}
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return NULL;
	}
	ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
	return ret;
}