/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:16:52 by kristori          #+#    #+#             */
/*   Updated: 2023/03/28 13:42:13 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_prompt *prompt, int in_fd)
{
	int	i;

	i = 0;
	while (prompt->envp[i])
	{
		write(in_fd, prompt->envp[i], ft_strlen(prompt->envp[i]));
		write(in_fd, "\n", 1);
		i++;
	}
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

static int	ft_check_exists(t_prompt *prompt)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (prompt->envp[i])
	{
		if (prompt->envp[i][j] == ((t_mini *)prompt->cmds->content)->full_cmd[1][j])
		{
			if ((prompt->envp[i][j] == '=') && (((t_mini *)prompt->cmds->content)->full_cmd[1][j] == '='))
			{
				prompt->envp[i] = ft_strdup(((t_mini *)prompt->cmds->content)->full_cmd[1]);
				return (1);
			}
			j++;
		}
		else
		{
			j = 0;
			i++;
		}
	}
	return (0);
}

char	**ft_env_add_var(t_prompt *prompt)
{
	char	**ris;
	int		i;
	int		index;

	if (ft_check_exists(prompt) == 0)
	{
		index = ft_strchr_index(((t_mini *)prompt->cmds->content)->full_cmd[1], '=');
		if (index == -1 || ((t_mini *)prompt->cmds->content)->full_cmd[1][index + 1] == '\0')
			return (prompt->envp);
		i = 0;
		while (prompt->envp[i])
			i++;
		ris = (char **)malloc(sizeof(char *) * (i + 2));
		i = 0;
		while (prompt->envp[i])
		{
			ris[i] = ft_strdup(prompt->envp[i]);
			i++;
		}
		ris[i] = ft_strdup(((t_mini *)prompt->cmds->content)->full_cmd[1]);
		ris[++i] = 0;
		ft_free(prompt->envp);
		return (ris);
	}
	return (prompt->envp);
}

char	**ft_env_remove_var(t_prompt *prompt)
{
	char	**ris;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (prompt->envp[i])
		i++;
	ris = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (prompt->envp[i])
	{
		if (ft_strncmp(prompt->envp[i], ((t_mini *)prompt->cmds->content)->full_cmd[1], ft_strlen(((t_mini *)prompt->cmds->content)->full_cmd[1]) - 1))
		{
			ris[j] = ft_strdup(prompt->envp[i]);
			j++;
		}
		i++;
	}
	ris[j] = 0;
	ft_free(prompt->envp);
	return (ris);
}
