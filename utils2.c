/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 13:51:22 by kristori          #+#    #+#             */
/*   Updated: 2023/03/27 12:15:31 by javellis         ###   ########.fr       */
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

// void	ft_putstr(char *str, int outfile)
// {
// 	int	i;

// 	i = 0;
// 	while(str && str[i])
// 	{
// 		write(outfile, str[i], 1);
// 	}
// }