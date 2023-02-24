/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:48:47 by kristori          #+#    #+#             */
/*   Updated: 2023/02/24 11:10:36 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char *shell_prompt = "minishell> ";
	char *input;
	input = readline(shell_prompt);
	char **tmp = ft_cmdtrim(input, ' ');
	printf("n pipe: %d\n", ft_pipecount(tmp));
	char **ris = ft_cmdsubsplit(tmp);
	int i;
	i = 0;
	while (ris[i])
	{
		printf("ris[%d]: %s\n", i, ris[i]);
		i++;
	}
	return 0;
}
