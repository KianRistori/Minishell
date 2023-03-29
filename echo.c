/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:03:21 by kristori          #+#    #+#             */
/*   Updated: 2023/03/29 15:39:02 by javellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_prompt *prompt, int in_fd)
{
	char	*tmp;
	int		i;
	int		j;

	i = 1;
	while (((t_mini *)prompt->cmds->content)->full_cmd[i])
	{
		j = 0;
		while (((t_mini *)prompt->cmds->content)->full_cmd[i][j])
		{
			if (((t_mini *)prompt->cmds->content)->full_cmd[i][j] == '$' && ((t_mini *)prompt->cmds->content)->full_cmd[i][j + 1] == '?')
			{
				tmp = ft_itoa(g_status);
				write(in_fd, tmp, ft_strlen(tmp));
				free(tmp);
				j++;
			}
			else
				write(in_fd, &((t_mini *)prompt->cmds->content)->full_cmd[i][j], 1);
			j++;
		}
		write(in_fd, " ", 1);
		i++;
	}
	write(in_fd, "\n", 1);
}
