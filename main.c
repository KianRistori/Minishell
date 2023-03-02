/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:48:47 by kristori          #+#    #+#             */
/*   Updated: 2023/03/02 14:32:36 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char *prompt = "@minishell ";
	char *input;
	char *user = getenv("USER");
	char *shell_prompt = ft_strjoin(user, prompt);
	input = readline(shell_prompt);
	char **tmp = ft_cmdtrim(input, ' ');
	char **ris = ft_cmdsubsplit(tmp);
	int i;
	i = 0;
	while (ris[i])
	{
		printf("ris[%d]: %s\n", i, ris[i]);
		i++;
	}
	free(shell_prompt);
	free(input);
	ft_free(tmp);
	ft_free(ris);
	return 0;
}

//<Makefile cat| echo "$PWD 'hola'" ~/src | 'tr' -d / >outfile
