/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:48:47 by kristori          #+#    #+#             */
/*   Updated: 2023/03/21 14:12:25 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_prompt	*prompt;
	t_list		*list;
	(void)argc;
	(void)argv;

	char **tmp;
	char **ris;
	char *shell = "@minishell ";
	char *input;
	char *user = getenv("USER");
	char *shell_prompt = ft_strjoin(user, shell);
	prompt = (t_prompt *)malloc(sizeof(t_prompt));
	prompt->envp = ft_env_cpy(envp);
	while (1)
	{
		input = readline(shell_prompt);
		add_history(input);
		prompt->pid = fork();
		if (!prompt->pid)
		{
			list = NULL;
			tmp = ft_cmdtrim(input, ' ');
			ris = ft_cmdsubsplit(tmp);
			ft_strtrim_all(ris);
			ft_fill_struct(&list, ris, envp);
			prompt->cmds = list;
			ft_execute(prompt);
			ft_free(tmp);
			ft_free(ris);
			ft_free_list(list);
		}
		else
			waitpid(prompt->pid, NULL, 0);
	}
	free(shell_prompt);
	return 0;
}

//<Makefile cat| echo "$PWD 'hola'" ~/src | 'tr' -d / >outfile


//controllare quella cosa
