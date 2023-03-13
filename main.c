/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:48:47 by kristori          #+#    #+#             */
/*   Updated: 2023/03/13 16:46:59 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	// t_list	*list;
	// list = NULL;
	(void)argc;
	(void)argv;
	(void)envp;
	char *prompt = "@minishell ";
	char *input;
	char *user = getenv("USER");
	char *shell_prompt = ft_strjoin(user, prompt);
	input = readline(shell_prompt);
	char **tmp = ft_cmdtrim(input, ' ');
	char **ris = ft_cmdsubsplit(tmp);
	// ft_fill_struct(&list, ris, envp);
	int i = 0;
	while (ris[i])
	{
		printf("ris[%d]: %s\n", i, ris[i]);
		i++;
	}
	// while (list != NULL)
	// {
	// 	printf("scrive\n");
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
	return 0;
}

//<Makefile cat| echo "$PWD 'hola'" ~/src | 'tr' -d / >outfile
