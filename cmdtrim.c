/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:38:28 by kristori          #+#    #+#             */
/*   Updated: 2023/04/05 10:31:17 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substitute(char *str)
{
	char		*ris;
	char		*tmp;
	char		*tmp2;
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
			tmp2 = ft_strdup(tmp);
			free(tmp);
			tmp = ft_strjoin2(ft_strdup("$"), tmp2);
			free(tmp2);
			tmp2 = ft_strdup(tmp);
			ris = ft_strjoin2(ris, tmp2);
			free(tmp2);
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
		if (!ft_check_quotes(str, flag, i) && str[i] == set)
		{
			ris[k] = ft_strlcpy_quote(str, i, j);
			j = i;
			k++;
		}
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
		i++;
	}
}
