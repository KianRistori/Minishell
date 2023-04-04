/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:45:22 by kristori          #+#    #+#             */
/*   Updated: 2023/04/04 10:24:14 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_prompt *prompt)
{
	char	*buf;
	char	*path;

	if (chdir(((t_mini *)prompt->cmds->content)->full_cmd[1]) != 0)
		return ;
	if (ft_strcmp(((t_mini *)prompt->cmds->content)->full_cmd[1], "..") != 0)
	{
		buf = (char *)malloc(100 * sizeof(char));
		getcwd(buf, 100);
		path = ft_strjoin(buf, "/");
		path = ft_strjoin(path, ((t_mini *)prompt->cmds->content)->full_cmd[1]);
		chdir(path);
		free(buf);
		free(path);
	}
}
