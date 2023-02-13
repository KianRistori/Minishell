/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:12:25 by kristori          #+#    #+#             */
/*   Updated: 2023/02/13 16:38:47 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_env_add_var(char **envp, char *str)
{
	char **ris;
	int	i;

	i = 0;
	while (envp[i])
		i++;
	ris = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (envp[i])
	{
		ris[i] = ft_strdup(envp[i]);
		i++;
	}
	ris[i] = ft_strdup(str);
	ris[++i] = 0;
	return (ris);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
