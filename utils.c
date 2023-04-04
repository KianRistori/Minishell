/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:02:42 by kristori          #+#    #+#             */
/*   Updated: 2023/04/04 14:22:08 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strlcpy_quote(const char *src, size_t size, size_t start)
{
	char	*dst;
	size_t	i;
	int		j;

	j = 0;
	i = start;
	dst = (char *)malloc(sizeof(char) * (size - start) + 1);
	if (size > 0)
	{
		while (src[i] && i < (size))
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = '\0';
	}
	return (dst);
}

char	*ft_strtrim2(char *s1, char const *set)
{
	char	*ris;
	size_t	i;
	size_t	j;

	ris = 0;
	if (s1 != 0 && set != 0)
	{
		i = 0;
		j = ft_strlen(s1);
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[j - 1] && ft_strchr(set, s1[j - 1]) && j > i)
			j--;
		ris = (char *)malloc(sizeof(char) * (j - i + 1));
		if (ris)
			ft_strlcpy(ris, &s1[i], j - i + 1);
	}
	free(s1);
	return (ris);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (s1 == NULL)
		s1 = ft_calloc(1, 1);
	if (s2 == NULL)
		s2 = ft_calloc(1, 1);
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	free(s1);
	return (str);
}

int	ft_strchr_index(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (s[i] == (char)c)
		return (i);
	return (-1);
}

int	get_next_line(char **line)
{
	char	*buffer;
	char	c;
	int		i;
	int		r;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (0);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[i + 1] = '\0';
	*line = ft_strdup(buffer);
	free(buffer);
	return (r);
}
