char *ft_strchr(const char *s, int c)
{
	int i = 0;
	if (!s)
		return NULL;
	while(s[i] != c && s[i])
		i++;
	if (s[i] == c)
		return (&s[i]);
	else
		return NULL;
}

size_t ft_strlen(char *s)
{
	size_t ret = 0;
	if (!s || !s[0])
		return 0;
	while (s[ret])
		ret++;
	return ret;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i = 0;
	if (!src || !dest)
		return NULL;
	while (i < n)
	{
		((char *)dest)[i] = ((const char *)src)[i];
		i++;
	}
	return dest;
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
	if (!dest || !src || dest == src)
		return dest;
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	while (n--)
		((char *)dest)[n] = ((const char *)src)[n];
	return dest;
}

int str_app(char **s1, char *s2, size_t size2)
{
	size_t size1 = ft_strlen(*s1);
	char *tmp = malloc(size1 + size2 + 1);
	if (!tmp)
		return 0;
	if (*s1)
		ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return 1;
}

int str_append(char **s1, char *s2)
{
	return (str_app(s1, s2, ft_strlen(s2)));
}

char *get_next_line(int fd)
{
	static char d[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	ssize_t red_ret;
	char *tmp = ft_strchr(d, '\n');
	while (!tmp)
	{
		if (!str_append(&ret, d))
			return NULL;
		red_ret = read(fd, d, BUFFER_SIZE);
		if (red_ret <= 0)
		{
			d[0] = 0;
			if (ret && *ret)
				return ret;
			free(ret);
			return NULL;
		}
		d[red_ret] = 0;
		tmp = ft_strchr(d, '\n');
	}
    if (!str_app(&ret, d, tmp - d + 1))
    {
        free(ret);
        return NULL;
    }
	ft_memmove(d, tmp + 1, ft_strlen(tmp + 1) + 1);
	return ret;
}

/*int main()
{
    int fd = open("test.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (1);
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
}*/
