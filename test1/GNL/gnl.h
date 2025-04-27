#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H


#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

int main(void);
char *ft_strdup(char *src);
char *get_next_line(int fd);
#endif