#ifndef RIP_H
# define RIP_H

# include <unistd.h>
# include <stdio.h>

int ft_strlen(char *s);
int good_closed(char *s, int n);
void check_rip(char *str, int n, int i, int *small, int lvl);
void rip(char *str, int n, int i, int small, int lvl);

#endif