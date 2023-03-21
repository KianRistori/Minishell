/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:37:37 by kristori          #+#    #+#             */
/*   Updated: 2023/03/20 14:39:53 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*buf;

	buf = (char *)malloc(100*sizeof(char));
	getcwd(buf, 100);
	printf("%s\n", buf);
	free(buf);
}
