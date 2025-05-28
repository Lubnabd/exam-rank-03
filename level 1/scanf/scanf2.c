int scan_int(FILE *f, va_list ap)







int match_space(FILE *f)
{
    int c;

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
    return 0;
}

//??
int match_char(FILE *f, char c)
{
    int ch = fgetc(f);

    if (ch != EOF)
    {
        if ( c == ch)
            fgetc(f);
    }
    ungetc(c, f);
    return 0;
}

int scan_char(FILE *f, va_list ap)
{
    int c;
    char *cp = va_arg(ap, char *);

    c = fgetc(f);
    if (c == EOF)
        return 0;
    *cp = (char)c;
    return 0;
}

//?? did my own changes in here
int scan_int(FILE *f, va_list ap)
{
    int value = 0;
    int sign = 1;
    int *ip = va_arg(ap, int *);
    int ch;

    ch = fgetc(f);
    if (ch == EOF)
        return 0;
    if (isspace(ch))
        ch = fgetc(f);
    if ( ch == '-')
    {
        sign = -1;
        ch = fgetc(f);
    }
    if ( ch == '+')
        fgetc(f);
    if (!isdigit(ch)){
        ungetc(c, f);
        return 0;}
    while (isdigit(ch))
        value = value * 10 + ( i - '0');
        ch = fgetc(f);
    if (i != EOF)
        ungetc(i, f);
    *ip = value * sign;
    return 1;
}

int scan_string(FILE *f, va_list ap)
{
    int *sp = va_arg(ap , char *);
    int ch;
    int i = 0;

    ch = fgetc(f);
    while (ch != EOF && isspace(ch))
        ch = fgetc(f);
    if (ch == EOF)
        return 0;
    do
    {
        sp[i] = ch;
        i++;
        ch = fgetc(f);
    } while (ch != EOF && !isspace(ch));

    if (ch != EOF)
        ungetc(c, f);
    sp[i] = '\0';

    return (1);
}

int ft_scanf(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    int ret = ft_vfscanf(stdin, format, ap);
    va_end(ap);
    return (ret);
}

int main (void)
{
    int x;
    char str1[100];
    char *str2[200];


}