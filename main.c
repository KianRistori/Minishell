/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:48:47 by kristori          #+#    #+#             */
/*   Updated: 2023/04/03 17:05:22 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_prompt	*prompt;
	(void)argc;
	(void)argv;

	char **tmp;
	char **ris;
	char *input = NULL;
	char *shell = "@minishell ";
	char *user = getenv("USER");
	char *shell_prompt = ft_strjoin(user, shell);
	prompt = (t_prompt *)malloc(sizeof(t_prompt));
	prompt->envp = ft_env_cpy(envp);
	while (1)
	{
		prompt->cmds = NULL;
		signal(SIGINT, ft_sighandle);
		signal(SIGQUIT, SIG_IGN);
		input = readline(shell_prompt);
		if (!input)
			break ;
		if (input[0] != '\0')
		{
			add_history(input);
			tmp = ft_cmdtrim(input, ' ');
			ris = ft_cmdsubsplit(tmp);
			ft_strtrim_all(ris);
			ft_fill_struct(&prompt->cmds, ris, envp);
			ft_execute(prompt);
			ft_free(tmp);
			ft_free(ris);
			ft_free_list(prompt->cmds);
		}
		free(input);
	}
	rl_clear_history();
	ft_free(prompt->envp);
	free(prompt);
	free(shell_prompt);
	return 0;
}

//<Makefile cat| echo "$PWD 'hola'" ~/src | 'tr' -d / >outfile


//controllare quella cosa
