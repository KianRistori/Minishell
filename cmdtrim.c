/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:38:28 by kristori          #+#    #+#             */
/*   Updated: 2023/03/30 10:49:01 by javellis         ###   ########.fr       */
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
	int	index;
	ris = 0;
	i = 0;
	while (cmd[i])
	{
		index = ft_strchr_index(cmd[i], 60);
		if (index == -1)
			index = ft_strchr_index(cmd[i], 62);
		if (index == -1)
			index = ft_strchr_index(cmd[i], 124);
		if (index != -1 && (cmd[i][index + 1] != '\0' && index - 1 > 0))
			ris += 2;
		else if (index != -1 && (cmd[i][index + 1] != '\0' || index - 1 > 0))
			ris++;
		i++;
	}
	return (ris);
}

static char	*ft_substitute(char *str)
{
	char		*ris;
	char		*tmp;
	static int	flag;
	int			i;
	int			j;
	char		*env_var;

	j = 1;
	i = 0;
	ris = NULL;
	if (ft_strcmp(str, "$?") == 0)
		return (ft_strdup(str));
	if (!ft_strchr(str, '$'))
	{
		while (str[i])
		{
			if (str[i] == '\'')
				flag = !flag;
			i++;
		}
		return (str);
	}
	i = 1;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"' || str[i] == ' ' || str[i] == '\0')
			break ;
		if (str[i] == '\'')
			flag = !flag;
		i++;
	}
	if (flag == 0)
	{
		tmp = ft_strlcpy_quote(str, i, j);
		env_var = getenv(tmp);
		if (env_var)
			ris = ft_strjoin2(ris, env_var);
		else
		{
			tmp = ft_strjoin2(ft_strdup("$"), tmp);
			ris = ft_strjoin2(ris, tmp);
		}
		free(tmp);
	}
	else
	{
		tmp = ft_strlcpy_quote(str, i, j - 1);
		ris = ft_strjoin2(ris, tmp);
		free(tmp);
	}
	j = i;
	while (str[i])
	{
		if (str[i] == '\'')
			flag = !flag;
		i++;
	}
	tmp = ft_strlcpy_quote(str, i, j);
	ris = ft_strjoin2(ris, tmp);
	free(tmp);
	return (ris);
}

static void	ft_expand_path(char **cmd)
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

static void	ft_search_env(char **cmd)
{
	char	**split;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 1;
	while(cmd[i])
	{
		if (ft_strchr(cmd[i], '$'))
		{
			j = 1;
			split = ft_split2(cmd[i], '$');
			free(cmd[i]);
			cmd[i] = ft_substitute(split[0]);
			while (split[j])
			{
				tmp =  ft_substitute(split[j]);
				cmd[i] = ft_strjoin(cmd[i], tmp);
				free(tmp);
				j++;
			}
			ft_free(split);
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
	ris = (char **)malloc(sizeof(char *) * ((ft_countlist(cmd) + ft_pipecount(cmd) + 1)));
	while (cmd[i])
	{
		while (cmd[i][j])
		{
			if (cmd[i][j] == 60 || cmd[i][j] == 62 || cmd[i][j] == 124)
			{
				flag = 1;
				if (j - 1 != -1)
				{
					if (cmd[i][j - 1] != 0 && cmd[i][j - 1] != ' ')
					{
						ris[k] = ft_strlcpy_quote(cmd[i], j, 0);
						k++;
					}
				}
				ris[k] = ft_strdup((char [2]){cmd[i][j], '\0'});
				k++;
				if (cmd[i][j + 1] != 0)
				{
					ris[k] = ft_strlcpy_quote(cmd[i], ft_strlen(cmd[i]), j + 1);
					k++;
				}
				break ;
			}
			j++;
		}
		if (flag == 0)
		{
			ris[k] = ft_strdup(cmd[i]);
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
		// cmd[i] = ft_strtrim2(cmd[i], "\'");
		// cmd[i] = ft_strtrim2(cmd[i], "\"");
		i++;
	}
}
