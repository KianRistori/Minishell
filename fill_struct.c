/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:00:15 by kristori          #+#    #+#             */
/*   Updated: 2023/03/24 10:48:39 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*ft_fill_t_mini(char **cmd, char **envp, char **built_in)
{
	t_mini	*ris;
	int	i;
	int	j;

	i = 0;
	ris = (t_mini *)malloc(sizeof(t_mini));
	ris->infile = 0;
	ris->outfile = 0;
	ris->full_cmd = NULL;
	ris->full_path = NULL;
	ris->here_doc = NULL;
	ris->built_in = NULL;
	while (cmd[i])
	{
		j = 0;
		while (built_in[j])
		{
			if (ft_strcmp(cmd[i], built_in[j]) == 0)
				ris->built_in = ft_strdup(built_in[j]);
			j++;
		}
		if (ris->full_path == NULL)
			ris->full_path = ft_path(cmd[i], envp);
		if (ft_strchr(cmd[i], '<') && ft_strchr(cmd[i + 1], '<'))
		{
			ris->here_doc = ft_strdup(cmd[i + 2]);
			i++;
		}
		else if (ft_strchr(cmd[i], '<'))
		{
			ris->infile = open(cmd[i + 1], O_RDONLY);
			if (ris->infile < 0)
				exit(EXIT_FAILURE);
		}
		if (ft_strchr(cmd[i], '>') && ft_strchr(cmd[i + 1], '>'))
		{
			ris->outfile = open(cmd[i + 2], O_WRONLY | O_APPEND | O_CREAT , 0644);
			if (ris->outfile < 0)
				exit(EXIT_FAILURE);
			i++;
		}
		else if (ft_strchr(cmd[i], '>'))
		{
			ris->outfile = open(cmd[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (ris->outfile < 0)
				exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	// if (ris->outfile > 0)
	// 	ris->full_path = ft_path(cmd[2], envp);
	// else
	// 	ris->full_path = ft_path(cmd[0], envp);
	// if (!ris->full_path)
	// 	exit(EXIT_FAILURE);
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

static char	**ft_cmd_copy(char **cmd, int start, int end)
{
	char	**ris;
	int		i;

	i = 0;
	ris = (char **)malloc(sizeof(char *) * (end - start + 1));
	while (start < end)
	{
		ris[i] = ft_strdup(cmd[start]);
		i++;
		start++;
	}
	ris[i] = 0;
	return (ris);
}

static void	ft_add_last(t_list **head, t_mini *newData)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->content = newData;
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		last_node = *head;
		while (last_node->next != NULL)
		{
			last_node = last_node->next;
		}
		last_node->next = new_node;
	}
}

static char	**ft_fill_built_in(void)
{
	char	**ris;

	ris = (char **)malloc(sizeof(char *) * (7));
	ris[0] = ft_strdup("echo");
	ris[1] =  ft_strdup("cd");
	ris[2] =  ft_strdup("pwd");
	ris[3] =  ft_strdup("export");
	ris[4] =  ft_strdup("unset");
	ris[5] =  ft_strdup("env");
	ris[6] = 0;
	return (ris);
}

void	ft_fill_struct(t_list **begin, char **cmd, char **envp)
{
	char	**built_in;
	char	**tmp;
	t_mini	*mini;
	int		i;
	int		j;

	i = 0;
	j = 0;
	built_in = ft_fill_built_in();
	while (cmd[i])
	{
		while (cmd[j])
		{
			if (ft_strchr(cmd[j], '|'))
			{
				tmp = ft_cmd_copy(cmd, i, j);
				mini = ft_fill_t_mini(tmp, envp, built_in);
				ft_add_last(begin, mini);
				ft_free(tmp);
				j++;
				break;
			}
			else if (!cmd[j + 1])
			{
				tmp = ft_cmd_copy(cmd, i, j + 1);
				mini = ft_fill_t_mini(tmp, envp, built_in);
				ft_add_last(begin, mini);
				ft_free(tmp);
				j++;
				break;
			}
			j++;
		}
		i = j;
	}
	ft_free(built_in);
}
