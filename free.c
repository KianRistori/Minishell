/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:44:38 by kristori          #+#    #+#             */
/*   Updated: 2023/04/03 17:07:59 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_free_list(t_list *list)
{
	while (list != NULL)
	{
		ft_free(((t_mini *)list->content)->full_cmd);
		free(((t_mini *)list->content)->full_path);
		free(((t_mini *)list->content)->built_in);
		free(((t_mini *)list->content)->here_doc);
		list = list->next;
	}
}
