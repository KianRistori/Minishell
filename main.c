/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:48:47 by kristori          #+#    #+#             */
/*   Updated: 2023/03/01 16:06:42 by javellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*ft_substitute(char *str)
// {
// 	static int	flag;
// 	int			i;
// 	int			j;
// 	char		*ris;

// 	j = 1;
// 	i = 0;
// 	ris = NULL;
// 	//printf("i: %d, j: %d\n", i,j);
// 	while (str[i])
// 	{
// 		if (str[i] == '\'')
// 			flag = !flag;
// 		i++;
// 	}
// 	if (!ft_strchr(str, '$'))
// 		return (str);
// 	i = 1;
// 	while (str[i])
// 	{
// 		// printf("str[i]>: %c\n", str[i]);
// 		if (str[i] == '\'' || str[i] == '\"' || str[i] == ' ' || str[i] == '\0')
// 			break ;
// 		i++;
// 		// printf("i>: %d, j>: %d falg: %d\n", i,j, flag);
// 	}
// 	printf("str 1 = %s\n",ft_strlcpy_quote(str, i, j));
// 	if (flag == 0)
// 		ris = ft_strjoin(ris, getenv(ft_strlcpy_quote(str, i, j)));
// 	else
// 		ris = ft_strjoin(ris, ft_strlcpy_quote(str, i, j - 1));
// 	j = i;
// 	while (str[i])
// 		i++;
// 	// printf("i: %d, j: %d", i,j);
// 	printf("str 2 = %s\n",ft_strlcpy_quote(str, i, j));
// 	ris = ft_strjoin(ris, ft_strlcpy_quote(str, i, j));
// 	return (ris);
// }

int	main()
{
	//char *str = "$SHELL'dfdfd'";
	//printf("i: , j:\n");
	//printf("\nstr = %s\n", ft_substitute(str));
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
	// ft_free(tmp);
	ft_free(ris);
	return 0;
}

