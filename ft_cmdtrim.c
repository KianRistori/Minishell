/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:38:28 by kristori          #+#    #+#             */
/*   Updated: 2023/02/24 11:56:30 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strlcpy_quote(const char *src, size_t size, size_t start)
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

static int	ft_wordcount(char *str, char set)
{
	int		ris;
	int		flag[2];
	int		i;

	ris = 0;
	i = 0;
	flag[0] = 0;
	flag[1] = 0;
	while (str[i])
	{
		if (flag[0] == 0 && flag[1] == 0 && str[i] == set)
			ris++;
		if (str[i] == 34 && flag[0] == 1)
			flag[0] = 0;
		else if (str[i] == 34 && flag[0] == 0)
			flag[0] = 1;
		if (str[i] == 39 && flag[1] == 1)
			flag[1] = 0;
		else if (str[i] == 39 && flag[1] == 0)
			flag[1] = 1;
		i++;
	}
	return (ris + 1);
}

int	ft_pipecount(char **cmd)
{
	int	ris;
	int	i;

	ris = 0;
	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], 60) || ft_strchr(cmd[i], 62) || ft_strchr(cmd[i], 124))
			ris++;
		i++;
	}
	return (ris);
}

static void	ft_search_env(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '$'))
		{
			if (getenv(ft_strtrim(cmd[i], " $")))
				cmd[i] = ft_strdup(getenv(ft_strtrim(cmd[i], " $")));
			else
				cmd[i] = ft_strdup("");
		}
		i++;
	}
}

char	**ft_cmdsubsplit(char **cmd)
{
	char	**ris;
	char	**split;
	int		i;
	int		k;
	int		j;

	i = 0;
	k = 0;
	j = 0;
	ris = (char **)malloc(sizeof(cmd) + (sizeof(char *) * ft_pipecount(cmd)) + 1);
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], 39) || ft_strchr(cmd[i], 34))
		{
			ris[k] = cmd[i];
			k++;
		}
		else if (ft_strchr(cmd[i], 60) || ft_strchr(cmd[i], 62) || ft_strchr(cmd[i], 124))
		{

		}
		j = 0;
		i++;
	}
	ris[++k] = 0;
	return (ris);
}

char	**ft_cmdtrim(char *str, char set)
{
	char	**ris;
	int		flag[2];
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	flag[0] = 0;
	flag[1] = 0;
	printf("%d\n", ft_wordcount(str, set));
	ris = (char **)malloc(sizeof(char *) * ft_wordcount(str, set) + 1);
	while (str[i] != '\0')
	{
		if (flag[0] == 0 && flag[1] == 0 && str[i] == set)
		{
			ris[k] = ft_strlcpy_quote(str, i, j);
			j = i;
			k++;
		}
		if (str[i] == 34 && flag[0] == 1)
			flag[0] = 0;
		else if (str[i] == 34 && flag[0] == 0)
			flag[0] = 1;
		if (str[i] == 39 && flag[1] == 1)
			flag[1] = 0;
		else if (str[i] == 39 && flag[1] == 0)
			flag[1] = 1;
		i++;
	}
	ris[k] = ft_strlcpy_quote(str, i, j);
	ris[++k] = 0;
	ft_search_env(ris);
	return (ris);
}
