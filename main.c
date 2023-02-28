/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:48:47 by kristori          #+#    #+#             */
/*   Updated: 2023/02/28 16:44:56 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_substitute(char *str)
{
	static int	flag;
	int			i;
	int			j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			flag = !flag;
		i++;
	}
	if (!ft_strchr(str, '$'))
		return (str);
	i = 0;
	while (str[i])
	{
		if (flag == 0 && (str[i] == '\'' || str[i] == '\"' || str[i] == ' ' || str[i] == '\0'))
			i++;
		str = ft_strjoin(str, getenv(ft_strlcpy_quote(str, i, j)));
	}
	j = i;
	while (str[i])
		i++;
	str = ft_strjoin(str, ft_strlcpy_quote(str, i, j));
	return (str);
}

int	main()
{
	char *str = "echo $SHELL 'dfdfd'";
	printf("str = %s", ft_substitute(str));
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
	// // ft_free(tmp);
	// ft_free(ris);
	return 0;
}

