/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:38:28 by kristori          #+#    #+#             */
/*   Updated: 2023/02/28 16:21:09 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_strchr(cmd[i], 60) || ft_strchr(cmd[i], 62)
			|| ft_strchr(cmd[i], 124))
			ris++;
		i++;
	}
	return (ris);
}

static char	*ft_substitute(char *str)
{
	static int	flag;
	int			i;
	int			j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			flag = !flag;
		i++;
	}
	if (!ft_strchr(str, '$'))
		return (str);
	i = 0;
	while (str[i])
	{
		if (flag == 0 && (str[i] == '\'' || str[i] == '\"' || str[i] == ' ' || str[i] == '\0'))
			i++;
		str = ft_strjoin(str, getenv(ft_strlcpy_quote(str, i, j)));
	}
	j = i;
	while (str[i])
		i++;
	str = ft_strjoin(str, ft_strlcpy_quote(str, i, j));
	return (str);
}

static void	ft_search_env(char **cmd)
{
	char	**split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while(cmd[i])
	{
		if (ft_strchr(cmd[i], '$'))
		{
			split = ft_split2(cmd[i], '$');
			while (split[j])
			{
				split[j] = ft_substitute(split[j]);
				j++;
			}
		}
		i++;
	}
}

char	**ft_cmdsubsplit(char **cmd)
{
	char	**ris;
	int		flag;
	int		i;
	int		j;
	int		k;

	flag = 0;
	i = 0;
	j = 0;
	k = 0;
	ris = (char **)malloc(sizeof(char *) * ((ft_countlist(cmd) + (ft_pipecount(cmd) * 2) + 1)));
	while (cmd[i])
	{
		while (cmd[i][j])
		{
			if (cmd[i][j] == 60 || cmd[i][j] == 62 || cmd[i][j] == 124)
			{
				flag = 1;
				ris[k] = ft_strlcpy_quote(cmd[i], j, 0);
				k++;
				ris[k] = ft_strdup((char [2]){cmd[i][j], 0});
				k++;
				ris[k] = ft_strlcpy_quote(cmd[i], ft_strlen(cmd[i]), j + 1);
				k++;
				break ;
			}
			j++;
		}
		if (flag == 0)
		{
			ris[k] = cmd[i];
			k++;
		}
		i++;
		j = 0;
		flag = 0;
	}
	ris[k] = 0;
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
	ris = (char **)malloc(sizeof(char *) * (ft_wordcount(str, set) + 1));
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
