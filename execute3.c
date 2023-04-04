/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:07:10 by kristori          #+#    #+#             */
/*   Updated: 2023/04/04 17:09:45 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_pipefd(t_list *cmds, int *pipefd)
{
	if (cmds->next != NULL)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
}

void	ft_redirect_input(t_prompt *prompt,
	t_list *cmds, t_mini *cmd, int *pipefd)
{
	if (cmds->next != NULL && (cmd->built_in == NULL
			|| ft_strcmp(cmd->built_in, "echo") == 0))
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else
	{
		if (cmd->outfile > 0)
			dup2(cmd->outfile, STDOUT_FILENO);
		else if (cmd->outfile == 2)
			dup2(prompt->pid, STDERR_FILENO);
	}
}

void	ft_redirect_output(t_mini *cmd, t_data *data)
{
	if (cmd->infile > 0)
	{
		if (cmd->infile == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		data->input_fd = cmd->infile;
		dup2(data->input_fd, STDIN_FILENO);
		close(data->input_fd);
	}
	else if (data->in_fd != 0)
	{
		dup2(data->in_fd, STDIN_FILENO);
		close(data->in_fd);
	}
}

void	ft_execute_parent_process(t_list *cmds,
	t_data *data, pid_t pid, int *pipefd)
{
	if (data->in_fd != 0)
		close(data->in_fd);
	if (cmds->next != NULL)
	{
		close(pipefd[1]);
		data->in_fd = pipefd[0];
	}
	else
		data->in_fd = data->input_fd;
	waitpid(pid, &data->status, 0);
	if (WIFEXITED(data->status))
		data->status = WEXITSTATUS(data->status);
}

void	ft_execute_child_process(t_prompt *prompt,
	t_list *cmds, t_data *data, int *pipefd)
{
	t_mini	*cmd;

	cmd = cmds->content;
	ft_redirect_output(cmd, data);
	if (cmd->here_doc != NULL)
		ft_here_doc(prompt);
	ft_redirect_input(prompt, cmds, cmd, pipefd);
	if (cmd->built_in != NULL && cmds->next != NULL
		&& ft_strcmp(cmd->built_in, "echo") != 0)
	{
		ft_execve_built_in_fork(prompt, cmd->full_cmd[0], pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	if (cmd->full_path != NULL && (cmd->built_in == NULL
			|| ft_strcmp(cmd->built_in, "echo") == 0))
		execve(cmd->full_path, cmd->full_cmd, prompt->envp);
	else if (cmd->built_in == NULL)
	{
		printf("Command not found: %s\n", cmd->full_cmd[0]);
		exit(127);
	}
	exit(EXIT_FAILURE);
}
