/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:33:11 by kristori          #+#    #+#             */
/*   Updated: 2023/04/04 14:40:17 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_remove_char(char **cmd)
{
	int	ris;
	int	i;

	ris = 0;
	i = 0;
	while (cmd[i])
	{
		if (!ft_strchr(cmd[i], '>') && !ft_strchr(cmd[i], '<'))
			ris++;
		else
		{
			if (ft_strchr(cmd[i], '>') && ft_strchr(cmd[i + 1], '>'))
				i++;
			if (ft_strchr(cmd[i], '<') && ft_strchr(cmd[i + 1], '<'))
				i++;
			i++;
		}
		i++;
	}
	return (ris);
}

char	**ft_remove_char(char **cmd)
{
	char	**ris;
	int		i;
	int		k;

	i = 0;
	ris = (char **)malloc(sizeof(char *) * (ft_count_remove_char(cmd) + 1));
	i = 0;
	k = 0;
	while (cmd[i])
	{
		if (!ft_strchr(cmd[i], '>') && !ft_strchr(cmd[i], '<'))
			ris[k++] = ft_strdup(cmd[i]);
		else
		{
			if (ft_strchr(cmd[i], '>') && ft_strchr(cmd[i + 1], '>'))
				i++;
			if (ft_strchr(cmd[i], '<') && ft_strchr(cmd[i + 1], '<'))
				i++;
			i++;
		}
		i++;
	}
	ft_free(cmd);
	ris[k] = 0;
	return (ris);
}
