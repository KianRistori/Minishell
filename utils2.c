/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 13:51:22 by kristori          #+#    #+#             */
/*   Updated: 2023/04/04 11:06:22 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_countlist(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_get_shell_prompt(void)
{
	char	*ris;
	char	*shell;
	char	*user;

	shell = "@minishell ";
	user = getenv("USER");
	ris = ft_strjoin(user, shell);
	return (ris);
}
