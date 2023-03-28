/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:48:47 by kristori          #+#    #+#             */
/*   Updated: 2023/03/28 15:39:24 by kristori         ###   ########.fr       */
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
	char *input = NULL;
	char *shell = "@minishell ";
	char *user = getenv("USER");
	char *shell_prompt = ft_strjoin(user, shell);
	prompt = (t_prompt *)malloc(sizeof(t_prompt));
	prompt->envp = ft_env_cpy(envp);
	while (1)
	{
		list = NULL;
		signal(SIGINT, ft_sighandle);
		signal(SIGQUIT, SIG_IGN);
		input = readline(shell_prompt);
		if (!input)
			break ;
		if (input[0] != '\0')
		{
			add_history(input);
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
		free(input);
	}
	free(shell_prompt);
	return 0;
}

//<Makefile cat| echo "$PWD 'hola'" ~/src | 'tr' -d / >outfile


//controllare quella cosa
