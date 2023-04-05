/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:03:21 by kristori          #+#    #+#             */
/*   Updated: 2023/04/05 10:50:55 by javellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_flags(t_prompt *prompt, int in_fd, int *i, int *flag)
{
	while (((t_mini *)prompt->cmds->content)->full_cmd[i[0]][i[1]])
	{
		if (((t_mini *)prompt->cmds->content)->full_cmd[i[0]][i[1]] == '\'')
			flag[0] = !flag[0];
		if (((t_mini *)prompt->cmds->content)->full_cmd[i[0]][i[1]] == '-'
			&& ((t_mini *)prompt->cmds->content)
				->full_cmd[i[0]][i[1] + 1] == 'n')
		{
			flag[1] = 1;
			i[1]++;
		}
		else if (((t_mini *)prompt->cmds->content)->full_cmd[i[0]][i[1]] != '\''
			&& ((t_mini *)prompt->cmds->content)->full_cmd[i[0]][i[1]] != '\"')
			write(in_fd, &((t_mini *)prompt->cmds->content)
				->full_cmd[i[0]][i[1]], 1);
		i[1]++;
	}
}

static void	ft_print_spaces(t_prompt *prompt, int *i, int in_fd)
{
	if (((t_mini *)prompt->cmds->content)->full_cmd[i[0]] != 0)
	{
		if (((t_mini *)prompt->cmds->content)->full_cmd[i[0]][0] != 0
			&& ((t_mini *)prompt->cmds->content)->full_cmd[i[0] + 1] != 0
				&& ft_strncmp(((t_mini *)prompt->cmds->content)
					->full_cmd[i[0]], "-n", 2))
			write(in_fd, " ", 1);
	}
}

void	ft_echo(t_prompt *prompt, int in_fd)
{
	int		i[2];
	int		flag[2];

	flag[0] = 0;
	i[0] = 1;
	flag[1] = 0;
	while (((t_mini *)prompt->cmds->content)->full_cmd[i[0]])
	{
		i[1] = 0;
		if (ft_strchr(((t_mini *)prompt->cmds->content)->full_cmd[i[0]], '$')
			&& !ft_strchr(((t_mini *)prompt->cmds->content)
				->full_cmd[i[0]], '\'') && !flag[0])
			ft_print_var(((t_mini *)prompt->cmds->content)
				->full_cmd[i[0]], in_fd, prompt->envp);
		else
			ft_set_flags(prompt, in_fd, i, flag);
		ft_print_spaces(prompt, i, in_fd);
		i[0]++;
	}
	if (flag[1])
		write(in_fd, "%%", 1);
	write(in_fd, "\n", 1);
}
