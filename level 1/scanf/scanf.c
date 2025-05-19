#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <unistd.h>

int match_space(FILE *f)
{
    int c;

    c = fgetc(f);
    while (c != EOF)
    {
        if (!isspace(c))
        {
            ungetc(c, f); // put the character back into the file
            break;
        }
        c = fgetc(f); // read the next character
    }
    return (0);
}

int match_char(FILE *f, char c) // no need for a while loop here because the char is being checked only one time
{
    int ch;

    ch = fgetc(f);
	if (ch == c)
		return 1;
	if (ch != EOF)
		ungetc(ch, f);
    return (0);
}

int scan_char(FILE *f, va_list ap)
{
    int c;
    char *cp = va_arg(ap, char *);

    c = fgetc(f);
    if (c == EOF) //  we do if condition for one time only because it is only 1 char that is being checked
        return 0; // failed to read
    *cp = (char)c;
    return 1;
}

int scan_int(FILE *f, va_list ap)
{
    int i;
    int *ip = va_arg(ap, int *); // always in the scan function you need a pointer to the thing in the function (int, char, string)
    int value = 0;
    int sign = 1;

    i = fgetc(f);
    if (i == EOF)
        return 0;
    while (isspace(i))
        i = fgetc(f);
    if ( i == '-')
    {
        sign = -1;
        i = fgetc(f);
    }
    else if (i == '+')
        i = fgetc(f);

    if (!isdigit(i))
    {
        ungetc(i, f);
        return 0;
    }
    while(isdigit(i))
    {
        value = value * 10 + (i - '0');
        i = fgetc(f);
    }
    if (i != EOF)
        ungetc(i, f);
    *ip = value * sign;
    return 1;
}

int scan_string(FILE *f, va_list ap)
{
    int ch; // here i need a counter because it is a string so its not a one time thing
    char *sp = va_arg(ap, char *);
    int i = 0;

    ch = fgetc(f);
    while (ch != EOF && isspace(ch))
        ch = fgetc(f);
    if (ch == EOF)
        return (0); // why not ungetc?
    do
    {
        sp[i] = ch;
            i++;
        ch = fgetc(f); // why do keep doing this?
    } while (ch != EOF && !isspace(ch));

    if (ch != EOF)
        ungetc(ch, f);
    sp[i] = '\0';

    return (1);
}

int match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	if (ferror(f))
		return (EOF);
	return nconv;
}

int ft_scanf(const char *format, ...)
{
	va_list ap;
    va_start (ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return (ret);
}

int main (void)
{
    int x;
    char str[100];
    char str2[100];
    ft_scanf("%d %s %s", &x, str, str2);
    printf("%d %s %s\n", x, str, str2);
}