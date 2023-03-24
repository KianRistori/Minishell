/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:18:24 by kristori          #+#    #+#             */
/*   Updated: 2023/03/24 12:19:12 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_execve_built_in(t_prompt *prompt, char *str)
{
	if (ft_strcmp(str, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(str, "cd") == 0)
		ft_cd(prompt);
	else if (ft_strcmp(str, "env") == 0)
		ft_env(prompt);
	else if (ft_strcmp(str, "export") == 0)
		prompt->envp = ft_env_add_var(prompt);
	else if (ft_strcmp(str, "unset") == 0)
		prompt->envp = ft_env_remove_var(prompt);
	else if (ft_strcmp(str, "echo") == 0)
	{
		int k = 1;
		while (((t_mini *)prompt->cmds->content)->full_cmd[k])
		{
			ft_print_echo(prompt->envp, ((t_mini *)prompt->cmds->content)->full_cmd[k]);
			printf(" ");
			k++;
		}
		printf("\n");
	}
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

static void	ft_process(t_prompt *prompt, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("error\n");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (((t_mini *)prompt->cmds->content)->built_in != NULL)
		{
			ft_execve_built_in(prompt, ((t_mini *)prompt->cmds->content)->built_in);
			exit(EXIT_SUCCESS);
		}
		else
		{
			execve(((t_mini *)prompt->cmds->content)->full_path, ((t_mini *)prompt->cmds->content)->full_cmd, prompt->envp);
			// printf("command not found: %s\n", ((t_mini *) prompt->cmds->content)->full_cmd[0]);
			perror("command not found");
			exit(127);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
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
	int in_file;
	int out_file;
	int status;
	int		fd[2];

	list = prompt->cmds;
	in_file = 0;
	out_file = 0;
	while (prompt->cmds != NULL) {
		if (((t_mini *) prompt->cmds->content)->infile > 0)
			in_file = ((t_mini *) prompt->cmds->content)->infile;
		if (((t_mini *) prompt->cmds->content)->outfile > 0)
			out_file = ((t_mini *) prompt->cmds->content)->outfile;
		((t_mini *) prompt->cmds->content)->full_cmd = ft_remove_char(((t_mini *) prompt->cmds->content)->full_cmd);
		prompt->cmds = prompt->cmds->next;
	}
	prompt->cmds = list;
	printf("in_file: %d\n", in_file);
	printf("out_file: %d\n", out_file);
	if (in_file > 0)
		dup2(in_file, STDIN_FILENO);
	int k = ft_lstsize(prompt->cmds);
	int i = 0;
	if (k > 1)
	{
		if (pipe(fd) == -1)
			perror("error\n");
		while (i < k - 1)
		{
			ft_process(prompt, fd);
			i++;
			prompt->cmds = prompt->cmds->next;
		}
	}
	if (((t_mini *) prompt->cmds->content)->here_doc != NULL)
		ft_here_doc(prompt);
	if (out_file > 0)
		dup2(out_file, STDOUT_FILENO);
	if (((t_mini *) prompt->cmds->content)->built_in != NULL)
	{
		ft_execve_built_in(prompt, ((t_mini *) prompt->cmds->content)->built_in);
		status = 0;
	}
	else
	{
		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork error\n");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			execve(((t_mini *) prompt->cmds->content)->full_path, ((t_mini *) prompt->cmds->content)->full_cmd, prompt->envp);
			// printf("command not found: %s\n", ((t_mini *) prompt->cmds->content)->full_cmd[0]);
			perror("command not found");
			exit(127);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
		}
	}
	g_status = status;
}
