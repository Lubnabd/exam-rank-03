#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	ft_strlen(char *s);
int	ft_strchr(const char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*set_next(char *buffer);
char	*set_line(char *buffer);
char	*join_str(char *buffer, char *buf);
char	*read_line(int fd, char *res);
char	*get_next_line(int fd);

