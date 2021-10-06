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

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*buf;

	buf = (unsigned char *)s;
	while (n--)
		*buf++ = c;
	return (s);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (*dst && i < size)
	{
		++i;
		++dst;
	}
	while (*src && i + 1 < size)
	{
		*dst++ = *src++;
		++i;
	}
	if (i < size)
		*dst = '\0';
	while (*src++)
		++i;
	return (i);
}

// Left-shift src to dst by n.
// Vacated space on the right set to zero.
char	*ft_memcpy_rclr(char *dst, char *src, size_t n)
{
	char unsigned	*ds;
	char unsigned	*sr;
	size_t			len;

	if (!dst && !src)
		return (NULL);
	ds = dst;
	sr = src;
	len = n;
	while (n-- > 0)
		*ds++ = *sr++;
	while (len-- > 0)
		*sr-- = '\0';
	return (dst);
}
		 
char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE];
	static char	sink[4096];
	char		*needle;
	char		*temp;

	while(1)
	{
		ft_memset(buf, '\0', BUFFER_SIZE);
		// most likely EOF
		if (!read(fd, buf, BUFFER_SIZE))
		{
			//malloc
			//return copy sink
			printf("eof %s\n", sink);
			return (NULL);
		}
		ft_strlcat(sink, buf, 4096);
		needle = ft_strchr(sink, '\n');
		// not found
		if (needle == NULL)
		{
			continue ;
		}
		// found match
		break ;
	}
	temp = malloc((needle - sink) + 1);
	if (temp == NULL)
		return (NULL);
	temp[needle - sink] = '\0';
	ft_strlcat(temp, sink, (needle - sink) + 1);
	// shift left by 
	ft_memcpy_rclr(sink, needle + 1, 4096 - (needle - sink + 1));
	return (temp);
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
