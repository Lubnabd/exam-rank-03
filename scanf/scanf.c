//can i use getchar function? or no need since theres stdin function allowed ?

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int	c;

	c = fgetc(f);
	while (c != EOF)
	{
		if (!isspace(c))
		{
			ungetc(c, f);
			break;
		}
		c = fgetc(f);
	}
    return (0);
}
//*
int match_char(FILE *f, char c)
{
    int	ch;

	ch = fgetc(f);
	if (ch == c)
		return 1;
	if (ch != EOF)
		ungetc(ch, f);
    return (0);
}
//*
int scan_char(FILE *f, va_list ap)
{
	int 	ch;
	char	*cp;

	ch = fgetc(f);
    if (ch == EOF)
        return 0;
    cp = va_arg(ap, char *);
    *cp = (char)ch;
    return 1;
}
//*
int scan_int(FILE *f, va_list ap)
{
	int value = 0;
    int sign = 1;
    int ch;
	int	*ip;

    // Skip whitespace
    ch = fgetc(f);
    while (isspace(ch))
		ch = fgetc(f);
    // Handle sign
    if (ch == '-')
	{
        sign = -1;
		ch = fgetc(f);
	}
    else if (ch == '+')
        ch = fgetc(f);

    if (!isdigit(ch)) {
        if (ch != EOF)
            ungetc(ch, f);
        return 0;
    }

    // Parse digits
    while (isdigit(ch)) {
        value = value * 10 + (ch - '0');
        ch = fgetc(f);
    }

    if (ch != EOF)
        ungetc(ch, f);

    ip = va_arg(ap, int *);
    *ip = value * sign;
    return 1;
}
//*
int scan_string(FILE *f, va_list ap)
{
	char *str = va_arg(ap, char *);
    int ch;
    int count = 0;

    // Skip leading whitespace
	ch = fgetc(f);
    while (ch != EOF && isspace(ch))
		ch = fgetc(f);
    if (ch == EOF)
        return 0;
    // Read until next whitespace or EOF
    do {
        str[count] = ch;
		count++;
        ch = fgetc(f);
    } while (ch != EOF && !isspace(ch));

    if (ch != EOF)
        ungetc(ch, f);

    str[count] = '\0';
	if (count > 0)
		return (1);
	else
		return (0);
}

// FROM HERE AND BELOW IS A GIVEN CODE NO NEED TO WRITE IT
int	match_conv(FILE *f, const char **format, va_list ap)
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

	int c = fgetc(f);   //hello ->store 'h' in c and moves the pointer to 'e'
	if (c == EOF)
		return EOF;
	ungetc(c, f);		// return the pointer to 'h'

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
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list	ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return (ret);
}

int main(void)
{
	int x;
	char str[100];
	ft_scanf("%d%s", &x, str);
	printf("%d %s\n", x, str);
}