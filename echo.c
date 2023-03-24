/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:03:21 by kristori          #+#    #+#             */
/*   Updated: 2023/03/23 14:18:27 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_echo(char **envp, char *str)
{
	char	**split_str;
	char	**split_env;
	int		i;
	int		j;
	int		len;

	i = 1;
	j = 0;
	if (ft_strchr(str, '$') == NULL)
		printf("%s", str);
	else
	{
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
			j = 0;
			i++;
		}
	}
}
