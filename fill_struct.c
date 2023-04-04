/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:00:15 by kristori          #+#    #+#             */
/*   Updated: 2023/04/04 14:14:11 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ris[1] = ft_strdup("cd");
	ris[2] = ft_strdup("pwd");
	ris[3] = ft_strdup("export");
	ris[4] = ft_strdup("unset");
	ris[5] = ft_strdup("env");
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
	built_in = ft_fill_built_in();
	while (cmd[i])
	{
		j = i;
		while (cmd[j] && !ft_strchr(cmd[j], '|'))
			j++;
		tmp = ft_cmd_copy(cmd, i, j);
		mini = ft_fill_t_mini(tmp, envp, built_in);
		ft_add_last(begin, mini);
		ft_free(tmp);
		if (cmd[j])
			j++;
		i = j;
	}
	ft_free(built_in);
}
