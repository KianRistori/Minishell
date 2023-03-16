/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:48:47 by kristori          #+#    #+#             */
/*   Updated: 2023/03/16 11:49:34 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_prompt	*prompt;
	t_list		*list;
	list = NULL;
	(void)argc;
	(void)argv;

	prompt = (t_prompt *)malloc(sizeof(t_prompt));
	char *shell = "@minishell ";
	char *input;
	char *user = getenv("USER");
	char *shell_prompt = ft_strjoin(user, shell);
	input = readline(shell_prompt);
	char **tmp = ft_cmdtrim(input, ' ');
	char **ris = ft_cmdsubsplit(tmp);
	ft_strtrim_all(ris);
	ft_fill_struct(&list, ris, envp);
	prompt->cmds = list;
	prompt->envp = envp;
	ft_execute(prompt);
	// int i = 0;
	// while (ris[i])
	// {
	// 	printf("ris[%d]: %s\n", i, ris[i]);
	// 	i++;
	// }
	// while (list != NULL)
	// {
	// 	printf("out: %d\n", ((t_mini *)list->content)->outfile);
	// 	printf("in: %d\n", ((t_mini *)list->content)->infile);
	// 	printf("path: %s\n", ((t_mini *)list->content)->full_path);
	// 	while (((t_mini *)list->content)->full_cmd[i])
	// 	{
	// 		printf("list: %s\n", ((t_mini *)list->content)->full_cmd[i]);
	// 		i++;
	// 	}
	// 	i = 0;
	// 	list = list->next;
	// }



	free(shell_prompt);
	free(input);
	ft_free(tmp);
	ft_free(ris);
	ft_free_list(list);
	return 0;
}

//<Makefile cat| echo "$PWD 'hola'" ~/src | 'tr' -d / >outfile


//controllare quella cosa
