/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/25 15:22:38 by tvan-cit       #+#    #+#                */
/*   Updated: 2020/01/22 12:02:07 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		i;
	int		i2;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	i2 = 0;
	newstr = ((char*)malloc(sizeof(char) *
	((ft_strlen(s1) + ft_strlen(s2)) + 1)));
	if (!newstr)
		return (NULL);
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[i2] != '\0')
	{
		newstr[i] = s2[i2];
		i++;
		i2++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;
	size_t	len;

	len = ft_strlen(s1);
	ptr = (char*)malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int			i;

	i = 0;
	if (!src && !dst)
		return (dst);
	else if (src < dst)
	{
		i = (int)len - 1;
		while (i >= 0)
		{
			((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
			i--;
		}
	}
	else
	{
		while (i < (int)len)
		{
			((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
			i++;
		}
	}
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = NULL;
	while (*s)
	{
		if (*s == c)
		{
			ptr = (char*)s;
			return (ptr);
		}
		s++;
	}
	if (c == '\0')
		return ((char*)s);
	return (ptr);
}

int		ft_make_line(char *str, char **line, char *end)
{
	*end = '\0';
	(*line) = ft_strdup(str);
	if ((*line) == NULL)
	{
		free(str);
		return (-1);
	}
	str = ft_memmove(str, (end + 1), (ft_strlen(end + 1) + 1));
	return (1);
}

int		ft_end_of_file(char *str, char **line)
{
	int check;

	check = 0;
	if (str)
		check = ft_make_line(str, line, ft_strchr(str, '\0'));
	free(str);
	if (check == -1)
		return (-1);
	return (0);
}

char	*ft_read_more(char *str, int *ret)
{
	char	*buf;
	char	*tmp;

	buf = malloc(128 + 1);
	if (buf == 0)
	{
		free(str);
		return (0);
	}
	*ret = read(0, buf, 128);
	if (*ret < 0)
	{
		free(buf);
		free(str);
		return (0);
	}
	buf[*ret] = '\0';
	tmp = str;
	str = ft_strjoin(str, buf);
	free(tmp);
	free(buf);
	if (str == 0)
		return (0);
	return (str);
}

int		get_next_line(char **line)
{
	int			ret;
	static char	*str;
	int			check;

	if (str == NULL)
		str = ft_strdup("");
	if (!str)
		return (-1);
	if (ft_strchr(str, '\n') != NULL)
	{
		check = ft_make_line(str, line, ft_strchr(str, '\n'));
		if (check == -1)
			return (-1);
		return (1);
	}
	else
		str = ft_read_more(str, &ret);
	if (str == 0)
		return (-1);
	if (ret == 0)
		return (ft_end_of_file(str, line));
	return (get_next_line(line));
}
