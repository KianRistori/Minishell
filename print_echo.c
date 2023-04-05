/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:57:03 by javellis          #+#    #+#             */
/*   Updated: 2023/04/05 10:42:19 by javellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_var(char *str, int in_fd, char **envp)
{
	char	*tmp;
	int		i[3];

	i[0] = 0;
	i[2] = 0;
	tmp = ft_strtrim(str, "\'");
	str = ft_strtrim(tmp, "\"");
	free(tmp);
	while (str[i[0]])
	{
		i[2] = 0;
		while (str[i[0]] && str[i[0]] != '$')
			write(in_fd, &str[i[0]++], 1);
		i[1] = i[0];
		if (str[i[0] + 1] == '?')
			ft_print_status(tmp, in_fd, i);
		else
			ft_print_exported_var(str, in_fd, envp, i);
		i[0] = i[1];
		if (str[i[0]] == '\0')
			break ;
		i[0]++;
	}
	free(str);
}

void	ft_print_status(char *tmp, int in_fd, int *i)
{
	tmp = ft_itoa(g_status);
	write(in_fd, tmp, ft_strlen(tmp));
	free(tmp);
	i[1]++;
}

void	ft_print_exported_var(char *str, int in_fd, char **envp, int *i)
{
	char	*var;
	char	**split;

	while (str[i[1]] && str[i[1]] != ' '
		&& str[i[1]] != '\'' && str[i[1]] != '\"')
	{
		i[1]++;
		if (str[i[1]] && str[i[1] + 1] == '$')
			break ;
	}
	if ((int)ft_strlen(str) == i[1])
		var = ft_strlcpy_quote(str, i[1], i[0] + 1);
	else
		var = ft_strlcpy_quote(str, i[1] + 1, i[0] + 1);
	while (envp[i[2]])
	{
		split = ft_split(envp[i[2]], '=');
		if (!ft_strcmp(split[0], var))
			write(in_fd, split[1], ft_strlen(split[1]));
		ft_free(split);
		i[2]++;
	}
	free(var);
}
