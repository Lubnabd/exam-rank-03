#include <unistd.h>
#include <stdlib.h>

int ft_strlen(char *str)
{
    int i = 0;
    if (str)
    {
        while (str[i])
            i++;
    }
    return (i);
}
void ft_putstr_fd(char *str, int fd)
{
    if (str)
        write(fd, str, ft_strlen(str));
}
void ft_free(char **s1, char **s2, char *message)
{
    if (s1 && *s1)
    {
        free(*s1);
        *s1 = NULL;
    }
    if (s2 && *s2)
    {
        free(*s2);
        *s2 = NULL;
    }
    if (message)
        ft_putstr_fd(message, 2);
}
char *ft_strdup(char *str)
{
    char *d;
    int i = 0;

    if (!str)
        return (NULL);
    d = malloc(ft_strlen(str) + 1);
    if (!d)
        return(ft_putstr_fd("Error: malloc failed\n", 2), NULL);
    while (str[i])
    {
        d[i] = str[i];
        i++;
    }
    d[i] = '\0';
    return (d);
}
char *ft_strjoin(char *s1, char *s2)
{
    char *join;
    int i = 0, j = 0;

    if (!s1 && !s2)
        return (NULL);
    if (s1 && !s2)
        return (ft_strdup(s1));
    if (!s1 && s2)
        return (ft_strdup(s2));
    join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!join)
        return (ft_putstr_fd("Error: malloc failed\n", 2), NULL);
    while (s1[i])
        join[j++] = s1[i++];
    i = 0;
    while (s2[i])
        join[j++] = s2[i++];
    join[j] = '\0';

    return (join);
}
char *read_argv(void)
{
    char *buffer;
    char *tmp;
    char *str;
    int r;

    tmp = NULL;
    str = NULL;
    buffer = malloc(11);
    if (!buffer)
        return (ft_putstr_fd("Error: malloc failed\n", 2), NULL);
    while (1)
    {
        r = read(STDIN_FILENO, buffer, 10);
        if (r < 0)
            return (ft_free(&buffer, &str, "Error: read failed\n"), NULL);
        buffer[r] = '\0';
        if (r == 0)
            break;
        tmp = str;
        str = ft_strjoin(tmp, buffer);
        if (!str)
           return(ft_free(&buffer, &tmp, NULL), NULL);
        if (tmp)
            free(tmp);
    }
    free(buffer);
    return (str);
}
void    replace(char *str, int start, int size)
{
    while(str[start] && start < size)
        str[start++] = '*';
}
void    search_and_replace(char *str, char *find)
{
    int i = 0;
    int j;
    int start;

    while(str[i])
    {
        j = 0;
        if (str[i] == find[j])
        {
            while(str[i + j] == find[j])
                j++;
            if (!find[j])
                replace(str, i, i + j);
        }
        i++;
    }
}
int main(int argc, char **argv)
{
    char *str;

    (void)argv;
    if (argc == 2)
    {
        str = read_argv();
        if(!str)
            return(1);
        search_and_replace(str, argv[1]);
        ft_putstr_fd(str, 1);
        return (0);
    }
    return (1);
}
