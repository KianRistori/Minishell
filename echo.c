/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:03:21 by kristori          #+#    #+#             */
/*   Updated: 2023/03/28 16:48:32 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_var(char *str, int *flag, char **env, int in_fd)
{
	int i;
	char	**split_env;

	i = 0;
	if (flag[1] == 0)
	{
		while (env[i])
		{
			split_env = ft_split(env[i], '=');
			if (ft_strcmp(split_env[0], str))
				write(in_fd, split_env[1],ft_strlen(split_env[1]));
			i++;
		}
	}
	else
	{
		write(in_fd, "$",1);
		write(in_fd, str, ft_strlen(str));
	}
}

void	ft_echo(t_prompt *prompt, int in_fd)
{
	int	flag[2];
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 1;
	flag[0] = 0;
	flag[1] = 0;
	while (((t_mini *)prompt->cmds->content)->full_cmd[i])
	{
		j = 0;
		while (((t_mini *)prompt->cmds->content)->full_cmd[i][j])
		{
			if (((t_mini *)prompt->cmds->content)->full_cmd[i][j] != '$')
				write(in_fd, &((t_mini *)prompt->cmds->content)->full_cmd[i][j], 1);
			else if (((t_mini *)prompt->cmds->content)->full_cmd[i][j] == '\"')
				flag[0] = !flag[0];
			else if (((t_mini *)prompt->cmds->content)->full_cmd[i][j] == '\'')
				flag[1] = !flag[1];
			else
			{
				while (((t_mini *)prompt->cmds->content)->full_cmd[i][k] && ((t_mini *)prompt->cmds->content)->full_cmd[i][k] != ' '
					&& ((t_mini *)prompt->cmds->content)->full_cmd[i][k] != '\'' && ((t_mini *)prompt->cmds->content)->full_cmd[i][k] != '\"')
						k++;
				ft_print_var(ft_strlcpy_quote(((t_mini *)prompt->cmds->content)->full_cmd[i], j + 1,k), flag, prompt->envp, in_fd);
			}
			j++;
		}
		write(in_fd, " ", 1);
		i++;
	}
	write(in_fd, "\n", 1);
}
