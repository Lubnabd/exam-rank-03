#include "rip.h"

// test the last case in the subject 
/*_ ( ) _ ( ) _$
_ ( ) ( _ ) _$
( _ ) _ ( ) _$
( _ ) ( _ ) _$
( ( ) _ _ ) _$*/

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int good_closed(char *str, int n)
{
    int i = 0;
    int flag = 0;
    while (i < n)
    { // why not if else? and only if?
        if (str[i] == '(')
            flag++; // why not opposite flag--?? i believe it is okay try it 
        if (str[i] == ')')
            flag--;
        if (flag == -1) // ?? why
            return 0;
        i++;
    }
    if (flag == 0) // true
        return 1;
    return 0; // why did i do it twice?
}

void check_rip(char *str, int n, int i, int *small, int lvl)
{
    char tmp;
    if (good_closed(str, n)) //??
    {
        if (*small == -1)
            *small = lvl;
        else if (lvl < *small)
            *small = lvl;
    }
    while ( i < n)
    {
        tmp = str[i];
        str[i] = '_';
        lvl++;
        check_rip(str, n, i + 1, small, lvl); //do i always do the +1 in recursion?
        str[i] = tmp;
        lvl--;
        i++;
    }
}

void rip(char *str, int n, int i, int small, int lvl)
{
    char tmp;
    if (lvl > small)
        return ;
    if (good_closed(str, n) && lvl == small)
    {
        write (1, str, ft_strlen(str));
        write (1, "\n", 1);
        return ;
    }
    while ( i < n)
    {
        tmp = str[i];
        lvl++;
        str[i] = '_';
        rip(str, n, i + 1, small, lvl);
        str[i] = tmp;
        lvl--;
        i++;
    }
}

int main (int argc , char ** argv)
{
    int small = -1; //?? also if it is the same as the *small in check_rip why is it an int here?
    if (argc == 2)
    {
        check_rip(argv[1], ft_strlen(argv[1]), 0, &small, 0);
        rip(argv[1], ft_strlen(argv[1]), 0, small, 0);
    }
    else
        return 1;
}


