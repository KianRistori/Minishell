/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:03:21 by kristori          #+#    #+#             */
/*   Updated: 2023/03/30 17:18:14 by javellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_var(char *str, int in_fd, char **envp)
{
	int	i;
	int	j;
	int k;
	char	*var;
	char	**split;

	i = 0;
	k = 0;
	while (str[i])
	{
		k = 0;
		while (str[i] && str[i] != '$')
		{
			// printf("ok\n");
			write(in_fd, &str[i], 1);
			i++;
		}
		j = i;
		while (str[j] && str[j] != ' ' && str[j] != '\'' && str[j] != '\"')
		{
			j++;
			if (str[j + 1] == '$')
			{
				break;
			}
		}
		// printf("j :%d, i: %d, strlen: %ld\n", j , i + 1, ft_strlen(str));
		if ((int)ft_strlen(str) == j)
			var = ft_strlcpy_quote(str, j, i + 1);
		else
			var = ft_strlcpy_quote(str, j + 1, i + 1);
		// printf("vat :%s\n", var);
		while (envp[k])
		{
			split = ft_split(envp[k], '=');
			if (!ft_strcmp(split[0], var))
				write(in_fd, split[1], ft_strlen(split[1]));
			k++;
		}
		i = j;
		i++;
	}
	
}

void	ft_echo(t_prompt *prompt, int in_fd)
{
	char	*tmp;
	int		i;
	int		j;
	int		option;
	int		flag[3];

	i = 1;
	flag[0] = 0;
	flag[1] = 0;
	flag[2] = 0;
	option = 0;
	while (((t_mini *)prompt->cmds->content)->full_cmd[i])
	{
		j = 0;
		flag[2] = 0;
		// int k = 0;
		// while (((t_mini *)prompt->cmds->content)->full_cmd[k])
		// {
		// 	printf("cmd[%d] :%s\n",k, ((t_mini *)prompt->cmds->content)->full_cmd[k]);
		// 	k++;
		// }
		// printf("flag: %d\n", flag[0]);
		if (ft_strchr(((t_mini *)prompt->cmds->content)->full_cmd[i], '$') && !ft_strchr(((t_mini *)prompt->cmds->content)->full_cmd[i], '\'') && !flag[0])
			ft_print_var(((t_mini *)prompt->cmds->content)->full_cmd[i], in_fd, prompt->envp);
		else
		{
			// printf("ok\n");
			while (((t_mini *)prompt->cmds->content)->full_cmd[i][j])
			{
				if (((t_mini *)prompt->cmds->content)->full_cmd[i][j] == '\'')
					flag[0] = !flag[0];
				if (((t_mini *)prompt->cmds->content)->full_cmd[i][j] == '\"')
					flag[1] = !flag[1];
				if (((t_mini *)prompt->cmds->content)->full_cmd[i][j] == '-' && ((t_mini *)prompt->cmds->content)->full_cmd[i][j + 1] == 'n')
				{
					option = 1;
					j++;
				}
				else if (((t_mini *)prompt->cmds->content)->full_cmd[i][j] == '$' && ((t_mini *)prompt->cmds->content)->full_cmd[i][j + 1] == '?')
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
		}
		if (flag[0] || flag[1])
			write(in_fd, " ", 1);
		else
		{
			if (!flag[2])
			{
				write(in_fd, " ", 1);
				flag[2] = 1;
			}
		}
		i++;
	}
	if (option)
		write(in_fd, "%%", 1);
	write(in_fd, "\n", 1);
}
