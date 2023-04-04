/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:54:11 by kristori          #+#    #+#             */
/*   Updated: 2023/04/04 17:08:55 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init_data(t_data *data)
{
	data->in_fd = 0;
	data->input_fd = 0;
	data->status = 0;
}

static void	ft_execute_commands_exe(t_prompt *prompt,
	t_list *cmds, t_data *data, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		ft_execute_child_process(prompt, cmds, data, pipefd);
	else
		ft_execute_parent_process(cmds, data, pid, pipefd);
}

void	ft_execute_commands(t_prompt *prompt)
{
	int		pipefd[2];
	t_list	*cmds;
	t_data	*data;
	t_mini	*cmd;

	data = (t_data *)malloc(sizeof(t_data));
	ft_init_data(data);
	cmds = prompt->cmds;
	while (cmds != NULL)
	{
		cmd = cmds->content;
		ft_create_pipefd(cmds, pipefd);
		if (cmd->built_in != NULL && cmds->next == NULL)
		{
			ft_execve_built_in(prompt, cmd->full_cmd[0], cmd->outfile);
			data->status = 0;
		}
		else
			ft_execute_commands_exe(prompt, cmds, data, pipefd);
		cmds = cmds->next;
	}
	g_status = data->status;
	free(data);
}
