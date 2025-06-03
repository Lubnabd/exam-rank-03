#include <unistd.h> // read
#include <errno.h> // for perror
#include <stdio.h> // printf
#include <stdlib.h> // malloc, calloc, realloc, free
#include <string.h> // for strlen

# define BUFFER_SIZE 42

size_t ft_strlcat(char *dst, const char *src, size_t size)
{
    size_t i = 0;
    size_t dlen = 0;
    size_t slen = 0;

    while (src[slen])
        slen++;
    while (dst[dlen])
        dlen++;
    // copy loop //
    while (src[i] && i < size - dlen - 1) //Only copy as many characters as will fit safely in the dst buffer
    {
        dst[dlen + i] = src[i];
        i++;
    }
    dst[dlen + i] = '\0';
    return (dlen + slen);
}
//If size = 10, and dst is already 6 characters long, then: We can only copy 3 more characters from src //(10 - 6 - 1 = 3)

char *read_line()
{
    char *buffer; // Final string we are building up and returning
    char *new_buf; // Used when we expand the buffer with realloc
    char tmp[BUFFER_SIZE + 1]; // why not *tmp? // A temporary container to store each chunk we read
    int total_len = 0; // To track how long the final string is
    int bytes_read = 1; // To store how many bytes we read in each loop // from read

    buffer = calloc(BUFFER_SIZE + 1, 1); // focus here
    if (!buffer)
    {
        perror("calloc failed\n");
        return (NULL);
    }
    while (bytes_read > 0)
    {
        bytes_read = read(0, tmp, BUFFER_SIZE); // it reads till buffer size from fd 0 and stores it in tmp line 57
        if (bytes_read == -1)
        {
            free(buffer);
            perror("read failed\n");
            return (NULL);
        }
        tmp[bytes_read] = '\0';

        total_len = total_len + bytes_read; //how long your buffer should be.

        // void *realloc(void *ptr, size_t new_size);
        new_buf = realloc(buffer, total_len + 1); // focus here//You resize your buffer to fit the total characters read so far
        if (!new_buf)
        {
            free(buffer);
            perror("realloc failed\n");
            return (NULL);
        }
        buffer = new_buf;
        // buffer is the dest, tmp is the src, and total_len + 1 is the size
        ft_strlcat(buffer, tmp, total_len + 1); // Append the contents of tmp to buffer
    }
    return (new_buf);
}
/*🧠 What does ft_strlcat do?
It concatenates (tmp) to the end of (buffer) safely, not overflowing.
Think of it like pouring the contents of the small bucket (tmp) into the big box (buffer) without spilling.*/

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i = 0;
    size_t j;

    while ( i < n && (s1[i] || s2[i]))
    {
        j = (unsigned char)s1[i] - (unsigned char)s2[i];
        if (j == 0)
            i++;
        else
            return j; // Return the actual difference between the differing characters
    }
    return 0;
}

void fill_stars(char *res, int *res_i, int max_lex int len) // very important
{
    int j = 0;
    while (j < len && *res_i < max_len)
    {
        res[*res_i] = '*';
        (*res_i)++;
        j++;
    }
}

char *filter(char *buffer, char *target, int buf_len)
{
    char *res;
    int matched; //flag to tell if we matched target
	int i = 0; // current index in buffer
	int j = 0; // current index in res
	int t_len = strlen (target); // it is same as buf_len

    res = malloc(buf_len + 1);
    if (!res)
    {
        return (NULL); // not null here because incompatible pointer to integer conversion returning 'void *' from a function with result type 'int'
        free(buffer);
    }
    while (buffer[i])
    {
        matched = 0;
        if (ft_strncmp(&buffer[i], target, t_len) == 0) //checks whether the next t_len characters in buffer starting from position i exactly match the string target
        {
            fill_stars(res, &j, buf_len, t_len);
            i = i + t_len; // moves the i index forward by the length of the matched word
            matched = 1;
        }
        if (!matched)
            res[j++] = buffer[i++];
            /*Imagine:
		At i = 0: 'h' != 'b' → Not matched
		So copy 'h' to res[0], advance both i and res_i by 1*/
    }
    res[j] = '\0';
    return (res);
}

int main (int argc, char **argv)
{
    char *buffer;
    char *res;

    if (argc == 2 && argv[1][0])
    {
        buffer = read_line();
        if (!buffer)
            return 1;
        res = filter(buffer, argv[1], strlen(buffer));
        if (!res)
        {
            perror("allocation failed");
		    return (1); // not null here because incompatible pointer to integer conversion returning 'void *' from a function with result type 'int'
        }
        printf("%s", res); //prints the final filtered string (res) to the screen.
        free(res);
        free(buffer);
    }
    else
        return 1;
}

// when testing the code without echo you can see the result after ctrl + d //
// ask about ifndef and endif?
// how to debug a segfault?