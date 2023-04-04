/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_t_mini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:23:07 by kristori          #+#    #+#             */
/*   Updated: 2023/04/04 14:24:44 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_built_in(char **cmd, char **built_in)
{
	int		i;
	int		j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (built_in[j])
		{
			if (ft_strcmp(cmd[i], built_in[j]) == 0)
				return (ft_strdup(built_in[j]));
			j++;
		}
		i++;
	}
	return (NULL);
}

static char	*get_full_path(char **cmd, char **envp)
{
	char	*path;
	int		i;

	i = 0;
	while (cmd[i])
	{
		path = ft_path(cmd[i], envp);
		if (!access(cmd[i], X_OK))
			return (ft_strdup(cmd[i]));
		else if (path)
			return (path);
		i++;
	}
	return (NULL);
}

static int	get_input_file(char **cmd)
{
	int		i;
	int		fd;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '<') && ft_strchr(cmd[i + 1], '<'))
			i++;
		else if (ft_strchr(cmd[i], '<'))
		{
			fd = open(cmd[i + 1], O_RDONLY);
			if (fd < 0)
				exit(EXIT_FAILURE);
			return (fd);
		}
		i++;
	}
	return (0);
}

static int	get_output_file(char **cmd)
{
	int		i;
	int		fd;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '>') && ft_strchr(cmd[i + 1], '>'))
		{
			fd = open(cmd[i + 2], O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (fd < 0)
				exit(EXIT_FAILURE);
			return (fd);
		}
		else if (ft_strchr(cmd[i], '>'))
		{
			fd = open(cmd[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd < 0)
				exit(EXIT_FAILURE);
			return (fd);
		}
		i++;
	}
	return (0);
}

t_mini	*ft_fill_t_mini(char **cmd, char **envp, char **built_in)
{
	t_mini	*ris;
	int		i;

	ris = (t_mini *)malloc(sizeof(t_mini));
	if (!ris)
		exit(EXIT_FAILURE);
	ris->full_path = get_full_path(cmd, envp);
	ris->built_in = get_built_in(cmd, built_in);
	ris->infile = get_input_file(cmd);
	ris->outfile = get_output_file(cmd);
	ris->here_doc = get_here_doc(cmd);
	i = 0;
	while (cmd[i])
		i++;
	ris->full_cmd = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (cmd[i])
	{
		ris->full_cmd[i] = ft_strdup(cmd[i]);
		i++;
	}
	ris->full_cmd[i] = 0;
	return (ris);
}
