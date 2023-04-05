/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtrim2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:12:28 by kristori          #+#    #+#             */
/*   Updated: 2023/04/05 11:01:02 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_search_env(char **cmd)
{
	char	**split;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '$'))
		{
			j = 1;
			split = ft_split2(cmd[i], '$');
			free(cmd[i]);
			cmd[i] = ft_substitute(split[0]);
			while (split[j])
			{
				tmp = ft_substitute(split[j]);
				cmd[i] = ft_strjoin(cmd[i], tmp);
				free(tmp);
				j++;
			}
			ft_free(split);
		}
		i++;
	}
}

void	ft_expand_path(char **cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '~'))
		{
			tmp = ft_strtrim2(cmd[i], " ~");
			cmd[i] = ft_strjoin(getenv("HOME"), tmp);
			free(tmp);
		}
		i++;
	}
}

int	ft_wordcount(char *str, char set)
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
