/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:12:25 by kristori          #+#    #+#             */
/*   Updated: 2023/02/14 15:43:49 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_char(char *str, char c)
{
	char	*ris;
	int		i;
	int		j;

	i = -1;
	while (str[++i])
	{
		if (str[i] != c)
			j++;
	}
	ris = (char *)malloc(sizeof(char) * (j + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			ris[j] = str[i];
			j++;
		}
		i++;
	}
	ris[j] = '\0';
	free(str);
	return (ris);
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

char	**ft_env_add_var(char **envp, char *str)
{
	//check se la variabile esiste gia' nel caso la sovrascrive
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
	str = ft_remove_char(str, 39);
	str = ft_remove_char(str, 34);
	ris[i] = ft_strdup(str);
	ris[++i] = 0;
	ft_free(envp);
	return (ris);
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
