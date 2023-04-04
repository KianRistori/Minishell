/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:18:24 by kristori          #+#    #+#             */
/*   Updated: 2023/04/04 17:10:23 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execve_built_in(t_prompt *prompt, char *str, int out_fd)
{
	if (out_fd == 0)
		out_fd = 1;
	if (ft_strcmp(str, "pwd") == 0)
		ft_pwd(out_fd);
	else if (ft_strcmp(str, "cd") == 0)
		ft_cd(prompt);
	else if (ft_strcmp(str, "env") == 0)
		ft_env(prompt, out_fd);
	else if (ft_strcmp(str, "export") == 0)
		prompt->envp = ft_env_add_var(prompt);
	else if (ft_strcmp(str, "unset") == 0)
		prompt->envp = ft_env_remove_var(prompt);
	else if (ft_strcmp(str, "echo") == 0)
		ft_echo(prompt, out_fd);
	return (0);
}

void	ft_execve_built_in_fork(t_prompt *prompt, char *str, int in_fd)
{
	if (ft_strcmp(str, "pwd") == 0)
		ft_pwd(in_fd);
	else if (ft_strcmp(str, "env") == 0)
		ft_env(prompt, in_fd);
	else if (ft_strcmp(str, "echo") == 0)
		ft_echo(prompt, in_fd);
}

void	ft_here_doc(t_prompt *prompt)
{
	pid_t	reader;
	int		fd[2];
	char	*line;
	t_mini	*cmds;

	cmds = ((t_mini *)prompt->cmds->content);
	if (pipe(fd) == -1)
		printf("error\n");
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (!ft_strncmp(line, cmds->here_doc, ft_strlen(cmds->here_doc)))
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(reader, NULL, 0);
	}
}

void	ft_execute(t_prompt *prompt)
{
	t_list	*list;

	list = prompt->cmds;
	while (prompt->cmds != NULL)
	{
		((t_mini *) prompt->cmds->content)->full_cmd
			= ft_remove_char(((t_mini *) prompt->cmds->content)->full_cmd);
		prompt->cmds = prompt->cmds->next;
	}
	prompt->cmds = list;
	ft_execute_commands(prompt);
}
