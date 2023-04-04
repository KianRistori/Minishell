/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:18:24 by kristori          #+#    #+#             */
/*   Updated: 2023/04/04 11:51:11 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_execve_built_in(t_prompt *prompt, char *str, int out_fd)
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
}

static void	ft_execve_built_in_fork(t_prompt *prompt, char *str, int in_fd)
{
	if (ft_strcmp(str, "pwd") == 0)
		ft_pwd(in_fd);
	else if (ft_strcmp(str, "env") == 0)
		ft_env(prompt, in_fd);
	else if (ft_strcmp(str, "echo") == 0)
		ft_echo(prompt, in_fd);
}

static void	ft_here_doc(t_prompt *prompt)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		printf("error\n");
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, ((t_mini *)prompt->cmds->content)->here_doc, ft_strlen(((t_mini *)prompt->cmds->content)->here_doc)) == 0)
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

static void ft_execute_commands(t_prompt *prompt)
{
	int		status;
	int		pipefd[2];
	pid_t	pid;
	int		in_fd = 0;
	int		input_fd = 0;

	t_list *cmds = prompt->cmds;
	while (cmds != NULL)
	{
		t_mini *cmd = cmds->content;

		if (cmds->next != NULL)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		if (cmd->built_in != NULL && cmds->next == NULL)
		{
			ft_execve_built_in(prompt, cmd->full_cmd[0], cmd->outfile);
			status =  0;
		}
		else
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (pid == 0)
			{
				if (cmd->infile > 0)
				{
					if (cmd->infile == -1)
					{
						perror("open");
						exit(EXIT_FAILURE);
					}
					input_fd = cmd->infile;
					dup2(input_fd, STDIN_FILENO);
					close(input_fd);
				}
				else if (in_fd != 0)
				{
					dup2(in_fd, STDIN_FILENO);
					close(in_fd);
				}
				if (cmd->here_doc != NULL)
					ft_here_doc(prompt);
				if (cmds->next != NULL && (cmd->built_in == NULL || ft_strcmp(cmd->built_in, "echo") == 0))
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
				if (cmd->built_in != NULL && cmds->next != NULL && ft_strcmp(cmd->built_in, "echo") != 0)
				{
					ft_execve_built_in_fork(prompt, cmd->full_cmd[0], pipefd[1]);
					exit(EXIT_SUCCESS);
				}
				if (cmd->full_path != NULL && (cmd->built_in == NULL || ft_strcmp(cmd->built_in, "echo") == 0))
				{
					execve(cmd->full_path, cmd->full_cmd, prompt->envp);
				}
				else if (cmd->built_in == NULL)
				{
					printf("Command not found: %s\n", cmd->full_cmd[0]);
					exit(127);
				}
				exit(EXIT_FAILURE);
			}
			else
			{
				if (in_fd != 0)
					close(in_fd);
				if (cmds->next != NULL)
				{
					close(pipefd[1]);
					in_fd = pipefd[0];
				}
				else
					in_fd = input_fd;
				waitpid(pid, &status, 0);
				if (WIFEXITED(status))
					status = WEXITSTATUS(status);
			}
		}
		cmds = cmds->next;
	}
	g_status = status;
}


static char	**ft_remove_char(char **cmd)
{
	char	**ris;
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (cmd[i])
	{
		if (!ft_strchr(cmd[i], '>') && !ft_strchr(cmd[i], '<'))
			k++;
		else
		{
			if (ft_strchr(cmd[i], '>') && ft_strchr(cmd[i + 1], '>'))
				i++;
			if (ft_strchr(cmd[i], '<') && ft_strchr(cmd[i + 1], '<'))
				i++;
			i++;
		}
		i++;
	}
	ris = (char **)malloc(sizeof(char *) * (k + 1));
	i = 0;
	k = 0;
	while (cmd[i])
	{
		if (!ft_strchr(cmd[i], '>') && !ft_strchr(cmd[i], '<'))
		{
			ris[k] = ft_strdup(cmd[i]);
			k++;
		}
		else
		{
			if (ft_strchr(cmd[i], '>') && ft_strchr(cmd[i + 1], '>'))
				i++;
			if (ft_strchr(cmd[i], '<') && ft_strchr(cmd[i + 1], '<'))
				i++;
			i++;
		}
		i++;
	}
	ft_free(cmd);
	ris[k] = 0;
	return (ris);
}

void	ft_execute(t_prompt *prompt)
{
	t_list *list;

	list = prompt->cmds;
	while (prompt->cmds != NULL)
	{
		((t_mini *) prompt->cmds->content)->full_cmd = ft_remove_char(((t_mini *) prompt->cmds->content)->full_cmd);
		prompt->cmds = prompt->cmds->next;
	}
	prompt->cmds = list;
	ft_execute_commands(prompt);
}
