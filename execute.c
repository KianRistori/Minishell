/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:18:24 by kristori          #+#    #+#             */
/*   Updated: 2023/03/16 16:19:24 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		wait(NULL);
	}
}

static void	ft_process(t_prompt *prompt)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		printf("error\n");
	pid = fork();
	if (pid == -1)
		printf("error\n");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execve(((t_mini *)prompt->cmds->content)->full_path, ((t_mini *)prompt->cmds->content)->full_cmd, prompt->envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
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
				i+=2;
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
				i+=2;
			if (ft_strchr(cmd[i], '<') && ft_strchr(cmd[i + 1], '<'))
				i++;
			i++;
		}
		i++;
	}
	ft_free(cmd);
	ris[k] = 0;
	// int l = 0;
	// while (ris[l])
	// {
	// 	printf("ris[%d]: %s\n", l, ris[l]);
	// 	l++;
	// }
	return (ris);
}

void	ft_execute(t_prompt *prompt)
{
	t_list *list;
	int in_file;
	int out_file;

	list = prompt->cmds;
	in_file = 0;
	out_file = 0;
	while (prompt->cmds != NULL)
	{
		if (((t_mini *)prompt->cmds->content)->infile > 0)
			in_file = ((t_mini *)prompt->cmds->content)->infile;
		if (((t_mini *)prompt->cmds->content)->outfile > 0)
			out_file = ((t_mini *)prompt->cmds->content)->outfile;
		((t_mini *)prompt->cmds->content)->full_cmd = ft_remove_char(((t_mini *)prompt->cmds->content)->full_cmd);
		prompt->cmds = prompt->cmds->next;
	}
	prompt->cmds = list;
	if (in_file > 0)
		dup2(in_file, STDIN_FILENO);
	int k = ft_lstsize(prompt->cmds);
	int i = 0;
	if (((t_mini *)prompt->cmds->content)->here_doc != NULL)
		ft_here_doc(prompt);
	else
	{
		if (k > 1)
		{
			while (i < k - 1)
			{
				ft_process(prompt);
				i++;
				prompt->cmds = prompt->cmds->next;
			}
		}
	}
	if (out_file > 0)
		dup2(out_file, STDOUT_FILENO);
	execve(((t_mini *)prompt->cmds->content)->full_path, ((t_mini *)prompt->cmds->content)->full_cmd, prompt->envp);
}
