/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:02:42 by kristori          #+#    #+#             */
/*   Updated: 2023/02/28 10:35:47 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strlcpy_quote(const char *src, size_t size, size_t start)
{
	char	*dst;
	size_t	i;
	int		j;

	j = 0;
	i = start;
	dst = (char *)malloc(sizeof(char) * (size - start) + 1);
	if (size > 0)
	{
		while (src[i] && i < (size))
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = '\0';
	}
	return (dst);
}

int		ft_countlist(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
