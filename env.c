/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:12:25 by kristori          #+#    #+#             */
/*   Updated: 2023/02/15 12:00:31 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_remove_char(char *str, char c)
{
	int writer;
	int reader;

	writer = 0;
	reader = 0;
	while (str[reader])
	{
		if (str[reader] != c)
			str[writer++] = str[reader];
		reader++;
	}
	str[writer] = 0;
}

char	**ft_env_cpy(char **envp)
{
	char	**ris;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	ris = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (envp[i])
	{
		ris[i] = ft_strdup(envp[i]);
		i++;
	}
	ris[i] = 0;
	return (ris);
}

int		ft_check_exists(char **envp, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (envp[i][j] == str[j])
		{
			if ((str[j] == '=') && (envp[i][j] == '='))
			{
				ft_remove_char(str, 39);
				ft_remove_char(str, 34);
				envp[i] = ft_strdup(str);
				return (1);
			}
			j++;
		}
		else
			i++;
	}
	return (0);
}

char	**ft_env_add_var(char **envp, char *str)
{
	char	**ris;
	int		i;

	if (ft_check_exists(envp, str) == 0)
	{
		i = 0;
		while (envp[i])
			i++;
		ris = (char **)malloc(sizeof(char *) * (i + 2));
		i = 0;
		while (envp[i])
		{
			ris[i] = ft_strdup(envp[i]);
			i++;
		}
		ft_remove_char(str, 39);
		ft_remove_char(str, 34);
		ris[i] = ft_strdup(str);
		ris[++i] = 0;
		ft_free(envp);
		return (ris);
	}
	return (envp);
}

char	**ft_env_remove_var(char **envp, char *str)
{
	char	**ris;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	ris = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str) - 1))
		{
			ris[j] = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
	ris[j] = 0;
	ft_free(envp);
	return (ris);
}
