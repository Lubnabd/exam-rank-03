#ifndef PERM_H
# define PERM_H

# include <stdlib.h>
# include <unistd.h>

int ft_strlen(char *s);
void ft_swap(char *a, char *b);
char *order(char *s);
int ft_strchr(const char *s, char c);
void permutations(char *s, char *res, int pos);

#endif