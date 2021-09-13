#include "get_next_line.h"

#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = (char)c;
	while (1)
	{
		if (*s == ch)
			return ((char *)s);
		if (*s == '\0')
			return (NULL);
		++s;
	}
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (src[i] && i + 1 < size)
		{
			dst[i] = src[i];
			++i;
		}
		dst[i] = 0;
	}
	while (src[i])
		++i;
	return (i);
}

// read into buffer.
// search for \n.
// strlcpy into string up to n + 1.
// TODO: manage buffer.
// 		 handle weird cases.		 
char	*get_next_line(int fd)
{
	size_t		len;
	int			r;
	static int	start;
	static char		buf[BUFFER_SIZE];
	char		*str;
	char		*line_end;

	if (buf[start] == '\0')
		r = read(fd, buf, BUFFER_SIZE - 1);
		buf[r] = '\0';
	line_end = ft_strchr(buf, '\n');
	printf("buf:\n%s", &buf[start]);
	if (line_end == NULL)
	{
		// reaching here means no NL found.
		// refill buffer.
		return (NULL);
	}
	else
	{
		// make 1 space for \n
		len = line_end - buf + 1;
		// make 1 space for nul-terminate
		str = malloc(sizeof(char) * len + 1);
		ft_strlcpy(str , &buf[start], len + 1);
		start += len;
	}
	return (str);
}

void main()
{
	char	*str;
	FILE *out=fopen("b.txt","r");

	str = get_next_line(fileno(out));
	if (str == NULL)
		return;
	printf("1st line: %s\n", str);
	free(str);
	str = get_next_line(fileno(out));
	if (str == NULL)
		return;
	printf("2nd line: %s\n", str);
	free(str);
	fclose(out);
}