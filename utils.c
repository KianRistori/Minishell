/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:02:42 by kristori          #+#    #+#             */
/*   Updated: 2023/03/02 14:02:24 by kristori         ###   ########.fr       */
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

char	*ft_strjoin2(char *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (s1 == NULL)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[j++] = s2[i];
		i++;
	}
	str[j] = '\0';
	free(s1);
	return (str);
}

int		ft_countlist(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
