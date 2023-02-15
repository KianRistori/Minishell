/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:19:07 by kristori          #+#    #+#             */
/*   Updated: 2023/02/15 15:42:27 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_echo(char **envp, char *str)
{
	char	**split_str;
	char	**split_env;
	int		i;
	int		j;
	int		k;
	int		len;

	i = 1;
	k = 0;
	j = 0;
	if (ft_strchr(str, '$') == NULL)
		printf("%s\n", str);
	else
	{
		// printf("str: %s\n", str);
		split_str = ft_split(str, '$');
		while (split_str[i])
		{
			while (envp[j])
			{
				split_env = ft_split(envp[j], '=');
				j++;
				if (ft_strlen(split_env[0]) > ft_strlen(split_str[i]))
					len = ft_strlen(split_env[0]);
				else
					len = ft_strlen(split_str[i]);
				if (!ft_strncmp(split_env[0], ft_strtrim(split_str[i], " "), len))
					printf("%s", split_env[1]);
			}
			while (split_str[i][k])
			{
				if (split_str[i][k] == ' ')
					printf(" ");
				k++;
			}
			k = 0;
			j = 0;
			i++;
		}
		printf("\n");
	}
}
