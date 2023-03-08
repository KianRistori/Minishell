/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:00:15 by kristori          #+#    #+#             */
/*   Updated: 2023/03/08 16:51:37 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*ft_fill_t_mini(char **cmd, char **envp)
{
	t_mini	*ris;
	int	i;

	i = 0;
	ris = (t_mini *)malloc(sizeof(t_mini));
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '<'))
		{
			ris->infile = open(cmd[i + 1], O_RDONLY);
			if (ris->infile < 0)
				exit(EXIT_FAILURE);
		}
		if (ft_strchr(cmd[i], '>'))
		{
			ris->outfile = open(cmd[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (ris->outfile < 0)
				exit(EXIT_FAILURE);
		}
	}
	i = 0;
	if (ris->outfile > 0)
		ris->full_path = ft_path(cmd[2], envp);
	else
		ris->full_path = ft_path(cmd[0], envp);
	if (!ris->full_path)
		exit(EXIT_FAILURE);
	while (cmd[i])
		i++;
	ris->full_cmd = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (cmd[i])
	{
		ris->full_cmd[i] = cmd[i];
		i++;
	}
	return (ris);
}

// static char	**ft_cmd_copy(char **cmd, int start, int end)
// {
// 	char	**ris;
// 	int		i;

// 	ris = (char **)malloc(sizeof(char *) * (end - start + 1));
// 	while (start < end)
// 	{
// 		ris[i] = ft_strdup(cmd[start]);
// 		i++;
// 		start++;
// 	}
// 	return (ris);

// }

// void	ft_fill_struct(t_list *begin, char **cmd, char **envp)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (cmd[i])
// 	{
// 		while (cmd[j])
// 		{
// 			if (ft_strchr(cmd[j], '|'))
// 				begin = ft_lstnew(ft_cmd_copy(cmd, i, j));
// 			j++;
// 		}
// 		i = j;
// 	}
// }
