/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:41:50 by kristori          #+#    #+#             */
/*   Updated: 2023/02/14 15:32:31 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

char	**ft_env_cpy(char **envp);
char	**ft_env_add_var(char **envp, char *str);
char	**ft_env_remove_var(char **envp, char *str);
char	*ft_remove_char(char *str, char c);
void	ft_free(char **str);

#endif
