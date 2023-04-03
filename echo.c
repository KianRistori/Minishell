/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:03:21 by kristori          #+#    #+#             */
/*   Updated: 2023/04/03 14:28:46 by javellis         ###   ########.fr       */
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
	char	*tmp;

	i = 0;
	k = 0;
	// printf("str :%s\n",str);
	str = ft_strtrim2(str, "\'");
	str = ft_strtrim2(str, "\"");
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
		if (str[j + 1] == '?')
		{
			tmp = ft_itoa(g_status);
			write(in_fd, tmp, ft_strlen(tmp));
			free(tmp);
			j++;
		}
		else
		{
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
			{
				// printf("\nok\n");
				var = ft_strlcpy_quote(str, j, i + 1);
			}
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
		}
		i = j;
		i++;
	}
	
}

void	ft_echo(t_prompt *prompt, int in_fd)
{
	int		i;
	int		j;
	int		option;
	int		flag;

	flag = 0;
	i = 1;
	option = 0;
	while (((t_mini *)prompt->cmds->content)->full_cmd[i])
	{
		j = 0;
		// int k = 0;
		// while (((t_mini *)prompt->cmds->content)->full_cmd[k])
		// {
		// 	printf("cmd[%d] :%s\n",k, ((t_mini *)prompt->cmds->content)->full_cmd[k]);
		// 	k++;
		// }
		if (ft_strchr(((t_mini *)prompt->cmds->content)->full_cmd[i], '$') && !ft_strchr(((t_mini *)prompt->cmds->content)->full_cmd[i], '\'') && !flag)
			ft_print_var(((t_mini *)prompt->cmds->content)->full_cmd[i], in_fd, prompt->envp);
		else
		{
			while (((t_mini *)prompt->cmds->content)->full_cmd[i][j])
			{
				if (((t_mini *)prompt->cmds->content)->full_cmd[i][j] == '\'')
					flag = !flag;
				if (((t_mini *)prompt->cmds->content)->full_cmd[i][j] == '-' && ((t_mini *)prompt->cmds->content)->full_cmd[i][j + 1] == 'n')
				{
					option = 1;
					j++;
				}
				else if(((t_mini *)prompt->cmds->content)->full_cmd[i][j] != '\'' && ((t_mini *)prompt->cmds->content)->full_cmd[i][j] != '\"')
					write(in_fd, &((t_mini *)prompt->cmds->content)->full_cmd[i][j], 1);
				j++;
			}
		}
		if (((t_mini *)prompt->cmds->content)->full_cmd[i][0] != 0 && ((t_mini *)prompt->cmds->content)->full_cmd[i + 1] != 0 
				&& ft_strncmp(((t_mini *)prompt->cmds->content)->full_cmd[i], "-n", 2))
			write(in_fd, " ", 1);
		i++;
	}
	if (option)
		write(in_fd, "%%", 1);
	write(in_fd, "\n", 1);
}