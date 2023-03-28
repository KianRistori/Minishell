/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:37:37 by kristori          #+#    #+#             */
/*   Updated: 2023/03/28 14:54:36 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(int in_fd)
{
	char	*buf;

	buf = (char *)malloc(100 * sizeof(char));
	getcwd(buf, 100);
	write(in_fd, buf, ft_strlen(buf));
	write(in_fd, "\n", 1);
	free(buf);
}
