/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 13:51:22 by kristori          #+#    #+#             */
/*   Updated: 2023/04/04 21:33:24 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_countlist(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_get_shell_prompt(void)
{
	char	*ris;
	char	*shell;
	char	*user;

	shell = "@minishell ";
	user = getenv("USER");
	ris = ft_strjoin(user, shell);
	return (ris);
}

char	*get_here_doc(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '<') && ft_strchr(cmd[i + 1], '<'))
			return (ft_strdup(cmd[i + 2]));
		i++;
	}
	return (NULL);
}

char	**ft_copy_add_envp(t_prompt *prompt)
{
	char	**ris;
	int		i;

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
}
