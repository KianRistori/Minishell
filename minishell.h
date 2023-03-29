/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javellis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:47:49 by kristori          #+#    #+#             */
/*   Updated: 2023/03/29 12:42:03 by javellis         ###   ########.fr       */
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
# include <signal.h>
# include <sys/ioctl.h>
# include <termios.h>

extern int g_status;

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
	char	*built_in;
	char	*here_doc;
}		t_mini;

char	*ft_strlcpy_quote(const char *src, size_t size, size_t start);
char	*ft_strjoin2(char *s1, char *s2);
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
int		get_next_line(char **line);

char	**ft_env_cpy(char **envp);

void	ft_pwd(int in_fd);
void	ft_cd(t_prompt *prompt);
void	ft_env(t_prompt *prompt, int in_fd);
char	**ft_env_add_var(t_prompt *prompt);
char	**ft_env_remove_var(t_prompt *prompt);
void	ft_echo(t_prompt *prompt, int in_fd);

void	ft_sighandle(int sig);

#endif
