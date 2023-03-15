/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <kristori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:47:49 by kristori          #+#    #+#             */
/*   Updated: 2023/03/15 12:32:47 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>

typedef struct s_prompt
{
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
}		t_prompt;

typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}		t_mini;

char	*ft_strlcpy_quote(const char *src, size_t size, size_t start);
char	*ft_strjoin2(char *s1, char const *s2);
char	*ft_strtrim2(char *s1, char const *set);
char	**ft_cmdtrim(char *str, char set);
char	**ft_cmdsubsplit(char **cmd);
void	ft_strtrim_all(char **cmd);
char	**ft_get_paths(char **envp);
char	*ft_path(char *cmd, char **envp);
void	ft_fill_struct(t_list **begin, char **cmd, char **envp);
int		ft_pipecount(char **cmd);
int		ft_countlist(char **str);
void	ft_free(char **str);
void	ft_free_list(t_list *list);
int		ft_strchr_index(const char *s, int c);
void	ft_execute(t_prompt *prompt);

#endif
