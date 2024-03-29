/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:37:06 by kristori          #+#    #+#             */
/*   Updated: 2022/10/06 16:47:28 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putchar_fd(('8'), fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd(('-'), fd);
		ft_putnbr_fd((-n), fd);
	}
	else
	{
		if (n > 9)
			ft_putnbr_fd((n / 10), fd);
		ft_putchar_fd((48 + n % 10), fd);
	}	
}
