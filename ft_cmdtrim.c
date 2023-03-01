/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:38:28 by kristori          #+#    #+#             */
/*   Updated: 2023/03/01 16:32:52 by javellis         ###   ########.fr       */
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
	char		*ris;

	j = 1;
	i = 0;
	ris = NULL;
	//printf("i: %d, j: %d\n", i,j);
	// while (str[i])
	// {
	// 	if (str[i] == '\'')
	// 		flag = !flag;
	// 	i++;
	// }
	if (!ft_strchr(str, '$'))
		return (str);
	i = 1;
	while (str[i])
	{
		// printf("str[i]>: %c\n", str[i]);
		// if (str[i] == '\'')
		// {
		// 	printf("flag prima = %d\n",flag);
		// 	flag = !flag;
		// 	printf("flag dopo = %d\n",flag);
		// }
		//printf("flag dopo = %d\n",flag);
		if (str[i] == '\'')
			flag = !flag;
		if (str[i] == '\'' || str[i] == '\"' || str[i] == ' ' || str[i] == '\0')
			break ;
		i++;
		// printf("i>: %d, j>: %d falg: %d\n", i,j, flag);
	}
	//printf("str 1 = %s\n",ft_strlcpy_quote(str, i, j));
	printf("flag = %d\n", flag);
	if (flag == 0)
		ris = ft_strjoin(ris, getenv(ft_strlcpy_quote(str, i, j)));
	else
		ris = ft_strjoin(ris, ft_strlcpy_quote(str, i, j - 1));
	j = i;
	while (str[i])
	{
		if (str[i] == '\'')
			flag = !flag;
		i++;
	}
	// while (str[i])
	// 	i++;
	// printf("i: %d, j: %d", i,j);
	// printf("str 2 = %s\n",ft_strlcpy_quote(str, i, j));
	ris = ft_strjoin(ris, ft_strlcpy_quote(str, i, j));
	return (ris);
}

//"$SHELL  df '$SHELL dfdfd'"

static void	ft_search_env(char **cmd)
{
	char	**split;
	int		i;
	int		j;

	i = 0;
	j = 1;
	while(cmd[i])
	{
		if (ft_strchr(cmd[i], '$'))
		{
			int k = 0;
			split = ft_split2(cmd[i], '$');
			while(split[k])
			{
				printf("split[k] = %s\n", split[k]);
				k++;
			}
			cmd[i] = split[0];
			while (split[j])
			{
				cmd[i] = ft_strjoin(cmd[i], ft_substitute(split[j]));
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
