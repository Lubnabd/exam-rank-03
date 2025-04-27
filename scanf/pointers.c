#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

void	plus_one(int *y)
{
	*y = *y + 1;
}

int main(void)
{
	int x = 5;
	plus_one(&x);
	printf("%d\n", x);
}
