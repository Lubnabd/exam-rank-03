#include <unistd.h> // read
#include <errno.h> // for perror
#include <stdio.h> // printf
#include <stdlib.h> // malloc, calloc, realloc, free
#include <string.h> // for strlen

# define BUFFER_SIZE 42

size_t ft_strlcat (char *dest, const char *src, size_t size)
{
	size_t i = 0;
	size_t dlen = 0;
	size_t slen = 0;

	while (src[slen] != '\0')
		slen++;
	while (dest[dlen] != '\0')
		dlen++;
	
	if (size <= dlen)
		return (size + slen);
	
	while (src[i] && i < size - dlen - 1)
	{
		dest[dlen + i] = src[i];
		i++;
	}
	dest[dlen + i] = '\0';
	return (dlen + slen);
}

char *read_input()
{
	char *buffer; // Final string we are building up and returning
	char *new_buffer; // Used when we expand the buffer with realloc
	int total_len = 0; // To track how long the final string is
	int bytes_read = 1; // To store how many bytes we read in each loop
	char tmp[BUFFER_SIZE + 1]; // why not *tmp? // A temporary container to store each chunk we read

	buffer = calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
	{
		perror("Error: calloc failed");
		return (NULL);
	}
	while (bytes_read > 0)
	{
		bytes_read = read(0, tmp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			perror("read failed");
			return (NULL);
		}
		tmp[bytes_read] = '\0';

		total_len = total_len + bytes_read; //how long your buffer should be.

		new_buffer = realloc(buffer, total_len + 1); //You resize your buffer to fit the total characters read so far
		if (!new_buffer)
		{
			free(buffer);
			perror("realloc failed");
			return (NULL);
		}

		buffer = new_buffer;
		ft_strlcat(buffer, tmp, total_len + 1); //  Append the contents of tmp to buffer
	}
	return (new_buffer);
}
/*🧠 What does ft_strlcat do?
It concatenates (tmp) to the end of (buffer) safely, not overflowing.
Think of it like pouring the contents of the small bucket (tmp) into the big box (buffer) without spilling.*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		t;
	size_t		i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		t = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (t == 0)
			i++;
		else
			return (t);
	}
	return (0);
}

void	fill_stars(char *res, int *res_i, int len)
{
	int	j;

	j = 0;
	while (j < len)
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
	int res_i = 0; // current index in res
	int t_len = strlen (target); // it is same as buf_len

	res = malloc(buf_len + 1);
	if (!res)
	{
		// can i free buffer here?
		perror("error malloc failed"); //??
		return (NULL);
	}
	while (buffer[i])
	{
		matched = 0;
		if (ft_strncmp(&buffer[i], target, t_len) == 0) // what does it do and what the point of == 0? //Do the next t_len characters starting from buffer[i] match the target?
		{
			fill_stars(res, &res_i, t_len);
			i = i + t_len; //?
			matched = 1; //??
		}
		if (!matched)
			res[res_i++] = buffer[i++];
		/*Imagine:
		At i = 0: 'h' != 'b' → Not matched
		So copy 'h' to res[0], advance both i and res_i by 1*/
	}
			res[res_i]= '\0';
			return (res);
}

int main (int argc , char **argv)
{
	char *buffer;
	char *res;

	if (argc == 2)
	{
		buffer = read_input();
		if (!buffer)
			return (1); // why 1?
		
		res = filter(buffer, argv[1], strlen(buffer));
		if (!res)
		{
			perror("Error: allocation failed\n");
			return (1);
		}
		printf("%s", res);
		free (res);
		free(buffer);
	}
	return 1; // not 0??
}