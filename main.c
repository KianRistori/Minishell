/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:48:47 by kristori          #+#    #+#             */
/*   Updated: 2023/04/04 11:50:27 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_loop(t_prompt *prompt, char *shell_prompt)
{
	char	**tmp;
	char	*input;

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
			tmp = ft_cmdsubsplit(tmp);
			ft_strtrim_all(tmp);
			ft_fill_struct(&prompt->cmds, tmp, prompt->envp);
			ft_execute(prompt);
			ft_free(tmp);
			ft_free_list(prompt->cmds);
		}
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt	*prompt;
	char		*shell_prompt;

	prompt = (t_prompt *)malloc(sizeof(t_prompt));
	prompt->envp = ft_env_cpy(envp);
	shell_prompt = ft_get_shell_prompt();
	(void)argc;
	(void)argv;
	ft_loop(prompt, shell_prompt);
	rl_clear_history();
	ft_free(prompt->envp);
	free(prompt);
	free(shell_prompt);
	return (0);
}

//<Makefile cat| echo "$PWD 'hola'" ~/src | 'tr' -d / >outfile
