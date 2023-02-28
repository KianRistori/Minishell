/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:23:19 by kristori          #+#    #+#             */
/*   Updated: 2023/02/28 15:32:51 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(const char *s, size_t n)
{
	char	*ris;
	size_t	i;

	i = 0;
	ris = NULL;
	if (n == 0)
		return (NULL);
	ris = (char *)malloc(sizeof(char) * (n) + 1);
	if (ris == 0)
		return (NULL);
	while (i < n)
	{
		ris[i] = s[i];
		i++;
	}
	ris[i] = '\0';
	return (ris);
}

static char	**ft_freeall(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static size_t	ft_wordcount(char const *s, char c)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 && s[i] != c)
			|| (s[i] == c && s[i + 1] != '\0' && s[i + 1] != c))
			k++;
		i++;
	}
	return (k);
}

char	**ft_split2(char const *s, char c)
{
	char	**ris;
	size_t	i;
	size_t	k;
	size_t	tmp;

	i = 0;
	k = 0;
	ris = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	while (i < ft_wordcount(s, c) && s[k] != '\0')
	{
		while (s[k] == c)
			k++;
		tmp = k;
		while (s[k] != c && s[k] != '\0')
			k++;
		if (tmp == 0)
			ris[i] = ft_strndup(&s[tmp], k - tmp);
		else
			ris[i] = ft_strndup(&s[tmp - 1], k - tmp + 1);
		if (ris[i++] == 0)
			return (ft_freeall(ris));
	}
	ris[i] = NULL;
	return (ris);
}
