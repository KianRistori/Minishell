/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:09:27 by kristori          #+#    #+#             */
/*   Updated: 2023/04/05 12:31:07 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_single_quote(char *str, int *flag)
{
	int	i;

	i = 0;
	if (ft_strcmp(str, "$?") == 0)
		return (ft_strdup(str));
	if (!ft_strchr(str, '$'))
	{
		while (str[i])
		{
			if (str[i] == '\'')
				*flag = !(*flag);
			i++;
		}
		return (str);
	}
	return (NULL);
}

static char	*substitute_env_var(char *var_name)
{
	char	*env_var;
	char	*tmp;
	char	*res;
	int		flag;

	flag = 0;
	env_var = getenv(var_name);
	if (!env_var)
	{
		tmp = ft_strjoin2(ft_strdup("$"), var_name);
		env_var = ft_strdup(tmp);
		free(tmp);
		flag = 1;
	}
	res = ft_strdup(env_var);
	if (flag == 1)
		free(env_var);
	return (res);
}

static char	*substitute_quotes(int flag, int i, int j, char *str)
{
	char	*res;
	char	*tmp;

	res = NULL;
	if (flag == 0)
	{
		tmp = ft_strlcpy_quote(str, i, j);
		res = substitute_env_var(tmp);
		free(tmp);
	}
	else
	{
		tmp = ft_strlcpy_quote(str, i, j - 1);
		res = ft_strdup(tmp);
		free(tmp);
	}
	return (res);
}

static int	ft_handle_quote(int *flag, char *str)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"' || str[i] == ' ' || str[i] == '\0')
			break ;
		if (str[i] == '\'')
			*flag = !(*flag);
	}
	return (i);
}

char	*ft_substitute(char *str)
{
	char		*ris;
	char		*tmp;
	static int	flag;
	int			i;
	int			j;

	j = 1;
	tmp = handle_single_quote(str, &flag);
	if (tmp)
		return (tmp);
	i = ft_handle_quote(&flag, str);
	ris = substitute_quotes(flag, i, j, str);
	j = i;
	while (str[i])
	{
		if (str[i] == '\'')
			flag = !flag;
		i++;
	}
	tmp = ft_strlcpy_quote(str, i, j);
	ris = ft_strjoin2(ris, tmp);
	free(tmp);
	return (ris);
}
