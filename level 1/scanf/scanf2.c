int match_space(FILE *f)
{
	int ch = fgetc(f);

	while (ch != EOF && isspace(ch))
		ch = fgetc(f);
	if (ch == EOF)
		return -1;
	ungetc(ch, f);
	return 0;
}

int match_char(FILE *f, char c) {
    int ch = fgetc(f);

    if (ch == EOF)
        return -1;
    if (ch == c)
        return 1;
    ungetc(ch, f);
    return 0;
}

int scan_char(FILE *f, va_list ap)
{
	int ch = fgetc(f);
    char *ptr = va_arg(ap, char*);

	if (ch == EOF)
		return -1;
	*ptr = ch ;
	return 1;
}

int scan_int(FILE *f, va_list ap)
{
	int res = 0;
	int sign = 1;
	int scanned = 0;
    int *ptr;
	int ch = fgetc(f);

    /*do
    {
        ch = fgetc(f);
    } while (ch != EOF && isspace(ch));
    if (ch == EOF)
        return -1;*/

    if (ch == '+' || ch == '-')
	{
		if (ch == '-')
			sign = -1;
		ch = fgetc(f);
	}

    while (ch != EOF && isdigit(ch))
	{
		res = res * 10 + (ch - '0');
		scanned++;
		ch = fgetc(f);
	}

    if (ch != EOF)
		ungetc(ch, f);

    if (scanned == 0)
		return 0;

    *ptr = va_arg(ap, int *);
	*ptr = res * sign;
	return 1;
}

int scan_string(FILE *f, va_list ap)
{
	char *str = va_arg(ap, char *);
	int scanned = 0;
	int ch = fgetc(f);

    /*do
    {
        ch = fgetc(f);
    } while (ch != EOF && isspace(ch));
    if (ch == EOF)
        return -1;*/

	while (ch != EOF && !isspace(ch))
	{
		str[scanned++] = ch;
		ch = fgetc(f);
	}
	if (ch != EOF)
		ungetc(ch, f);
	str[scanned] = '\0';

	if (scanned == 0)
		return 0;
	return (1);
}

// 82

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
		case '\0': /////////////////
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
	va_list ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}
