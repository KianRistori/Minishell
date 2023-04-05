/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:38:28 by kristori          #+#    #+#             */
/*   Updated: 2023/04/05 12:21:10 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cmdsubsplit_state(char **ris, int *i, int *flag, char **cmd)
{
	while (cmd[i[0]][i[1]])
	{
		if (cmd[i[0]][i[1]] == 60 || cmd[i[0]][i[1]] == 62
			|| cmd[i[0]][i[1]] == 124)
		{
			*flag = 1;
			if (i[1] - 1 != -1)
			{
				if (cmd[i[0]][i[1] - 1] != 0 && cmd[i[0]][i[1] - 1] != ' ')
					ris[i[2]++] = ft_strlcpy_quote(cmd[i[0]], i[1], 0);
			}
			ris[i[2]] = ft_strdup((char [2]){cmd[i[0]][i[1]], '\0'});
			i[2]++;
			if (cmd[i[0]][i[1] + 1] != 0)
			{
				ris[i[2]] = ft_strlcpy_quote(cmd[i[0]],
						ft_strlen(cmd[i[0]]), i[1] + 1);
				i[2]++;
			}
			break ;
		}
		i[1]++;
	}
}

char	**ft_cmdsubsplit(char **cmd)
{
	char	**ris;
	int		flag;
	int		i[3];

	flag = 0;
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	ris = (char **)malloc(sizeof(char *)
			* ((ft_countlist(cmd) + ft_pipecount(cmd) + 1)));
	while (cmd[i[0]])
	{
		ft_cmdsubsplit_state(ris, i, &flag, cmd);
		if (flag == 0)
		{
			ris[i[2]] = ft_strdup(cmd[i[0]]);
			i[2]++;
		}
		i[0]++;
		i[1] = 0;
		flag = 0;
	}
	ris[i[2]] = 0;
	ft_free(cmd);
	return (ris);
}

static int	ft_check_quotes(char *str, int *flags, int i)
{
	if (str[i] == 34 && flags[0] == 1)
		flags[0] = 0;
	else if (str[i] == 34 && flags[0] == 0)
		flags[0] = 1;
	if (str[i] == 39 && flags[1] == 1)
		flags[1] = 0;
	else if (str[i] == 39 && flags[1] == 0)
		flags[1] = 1;
	return (flags[0] || flags[1]);
}

char	**ft_cmdtrim(char *str, char set)
{
	char	**ris;
	int		flag[2];
	int		index[3];

	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	flag[0] = 0;
	flag[1] = 0;
	ris = (char **)malloc(sizeof(char *) * (ft_wordcount(str, set) + 1));
	while (str[index[0]] != '\0')
	{
		if (!ft_check_quotes(str, flag, index[0]) && str[index[0]] == set)
		{
			ris[index[2]] = ft_strlcpy_quote(str, index[0], index[1]);
			index[1] = index[0];
			index[2]++;
		}
		index[0]++;
	}
	ris[index[2]] = ft_strlcpy_quote(str, index[0], index[1]);
	ris[++index[2]] = 0;
	ft_search_env(ris);
	ft_expand_path(ris);
	return (ris);
}

void	ft_strtrim_all(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		cmd[i] = ft_strtrim2(cmd[i], " ");
		i++;
	}
}
