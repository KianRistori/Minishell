/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:18:24 by kristori          #+#    #+#             */
/*   Updated: 2023/03/15 12:46:07 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_child_one(t_prompt *prompt, int *pipefd)
{
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	execve(((t_mini *)prompt->cmds->content)->full_path, ((t_mini *)prompt->cmds->content)->full_cmd, prompt->envp);
}

static void	ft_child_two(t_prompt *prompt, int *pipefd)
{
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	execve(((t_mini *)prompt->cmds->next->content)->full_path, ((t_mini *)prompt->cmds->next->content)->full_cmd, prompt->envp);
}

void	ft_execute(t_prompt *prompt)
{
	if (ft_lstsize(prompt->cmds) == 1)
	{
		if (execve(((t_mini *)prompt->cmds->content)->full_path, ((t_mini *)prompt->cmds->content)->full_cmd, prompt->envp) == -1)
			printf("error\n");
	}
	else if (ft_lstsize(prompt->cmds) == 2)
	{
		int	pipefd[2];

		if (pipe(pipefd) < 0)
			perror("Error");
		prompt->pid = fork();
		if (!prompt->pid)
			ft_child_one(prompt, pipefd);
		else
			ft_child_two(prompt, pipefd);
	}
}
