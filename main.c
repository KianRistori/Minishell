/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:28:28 by kristori          #+#    #+#             */
/*   Updated: 2023/02/15 15:16:41 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char *shell_prompt = "minishell> ";
	char *input;
	char **input_split;
	char *buf;
	char *path;
	int	i = 0;
	char **envp_cpy = ft_env_cpy(envp);
	while (1)
	{
		input = readline(shell_prompt);
		input_split = ft_split(input, ' ');
		if (ft_strcmp(input, "exit") == 0)
			exit(0);
		if (ft_strcmp(input, "pwd") == 0)
		{
			buf=(char *)malloc(100*sizeof(char));
			getcwd(buf,100);
			printf("%s\n", buf);
		}
		if (ft_strcmp(input_split[0], "cd") == 0)
		{
			if (chdir(input_split[1]) != 0)
				break ;
			if (ft_strcmp(input_split[1], "..") != 0)
			{
				buf=(char *)malloc(100*sizeof(char));
				getcwd(buf, 100);
				path = ft_strjoin(buf, "/");
				path = ft_strjoin(path, input_split[1]);
				chdir(path);
			}
		}
		if (ft_strcmp(input_split[0], "export") == 0)
			envp_cpy = ft_env_add_var(envp_cpy, input_split[1]);
		if (ft_strcmp(input_split[0], "unset") == 0)
			envp_cpy = ft_env_remove_var(envp_cpy, input_split[1]);
		if (ft_strcmp(input_split[0], "env") == 0)
		{
			while (envp_cpy[i])
			{
				printf("%s\n", envp_cpy[i]);
				i++;
			}
		}
		if (ft_strcmp(input_split[0], "echo") == 0)
			ft_print_echo(envp_cpy, input);
		i = 0;
		add_history(input);
		free(input);
	}
	free(shell_prompt);
	return 0;
}
