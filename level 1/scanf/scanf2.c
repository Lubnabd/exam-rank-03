#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int ch = fgetc(f);
    while (ch != EOF)
    {
        if (!isspace(ch))
        {
            ungetc(ch, f);
            break ;
        }
        ch = fgetc(f);
    }
    return 0;
}

int match_char(FILE *f, char c)
{
    int ch = fgetc(f);
    if (ch == c)
        return 1;
    if (ch != EOF)
        ungetc(ch, f);
    return 0;
}

int scan_char(FILE *f, va_list ap)
{
    int ch = fgetc(f);
    char *cp = va_arg(ap, char *);

    if (ch == EOF)
        return 0;
    *cp = (char) ch;
    return 1;
}

int scan_int(FILE *f, va_list ap)
{
    int value = 0;
    int sign = 1;
    int *ip = va_arg (ap , int *);
    int ch = fgetc(f);

    if (ch == EOF)
        return 0;
    while (isspace(ch))
        ch = fgetc(f); // fgetc Read until non-whitespace
    if (ch == '-')
    {
        sign = -1;
        ch = fgetc(f);
    }
    else if (ch == '+')
        ch = fgetc(f);
    if (!isdigit(ch)) // if not while
    {
        ungetc(ch, f);
        return 0; // you keep forgetting 0
    }
    while (isdigit(ch))
    {
        value = value * 10 + (ch - '0');
        ch = fgetc(f);
    }
    if (ch != EOF)
        ungetc(ch, f);
    *ip = value * sign;
    return 1;
}

int scan_string(FILE *f, va_list ap)
{
    int i = 0;
    int ch = fgetc(f);
    char *sp = va_arg(ap, char *);

    while (ch != EOF && isspace(ch))
        ch = fgetc(f);; // fgetc here// You do ungetc once, not in a loop.
    if (ch == EOF)
        return 0;
    do
    {
        sp[i] = ch;
        i++;
        ch = fgetc(f);
    } while (ch != EOF && !isspace(ch));
    if (ch != EOF)
        ungetc(ch, f);
    sp[i] = '\0'; // this should be the last thing(here)
    return 1;
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