/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:48:47 by kristori          #+#    #+#             */
/*   Updated: 2023/03/08 16:56:46 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	// char *prompt = "@minishell ";
	// char *input;
	// char *user = getenv("USER");
	// char *shell_prompt = ft_strjoin(user, prompt);
	// input = readline(shell_prompt);
	// char **tmp = ft_cmdtrim(input, ' ');
	// char **ris = ft_cmdsubsplit(tmp);
	// int i;
	// i = 0;
	// while (ris[i])
	// {
	// 	printf("ris[%d]: %s\n", i, ris[i]);
	// 	i++;
	// }
	// free(shell_prompt);
	// free(input);
	// ft_free(tmp);
	// ft_free(ris);
	// char *str = "fskdfh";
	// char **paths = ft_get_paths(envp);
	// int i = 0;
	// while (paths[i])
	// {
	// 	printf("%s\n", paths[i]);
	// 	i++;
	// }
	// char *path = ft_path(str, envp);
	// if (path)
	// 	write(1, path, ft_strlen(path));
	// free(path);
	// ft_free(paths);


	int	i;
	int	j;

	char **cmd = malloc(sizeof(char *)* 8);
	cmd[0] = "MAKEFILE";
	cmd[1] = "MAILE";
	cmd[2]	 = "|";
	cmd[3] = "MAkeleLE";
	cmd[4]	 = "|";
	cmd[5] = "MAkeleLE";
	cmd[6] = "MAkeleLE";
	cmd[7]  = 0;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		while (cmd[j])
		{
			if (ft_strchr(cmd[j], '|'))
				printf("i = %d, j = %d\n", i, j);
				//begin = ft_lstnew(ft_cmd_copy(cmd, i, j));
			j++;
		}
		i = j;
	}
	return 0;
}



//<Makefile cat| echo "$PWD 'hola'" ~/src | 'tr' -d / >outfile
