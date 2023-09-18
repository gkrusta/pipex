/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:04:22 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/18 15:15:07 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"

typedef struct s_pipex {
	pid_t	pid;
	int		infile_fd;
	int		outfile_fd;
	int		end[2];
	int		i;
	char	*cmd;
	char	**path;
	char	**cmd_arg;
}				t_pipex;

/* piping process & forking */
void	pipex_bonus(t_pipex *p, char **argv, char **envp, int argc);
void	last_process(t_pipex *p, char **envp, char *cmd_last);
void	parent_process(t_pipex *p);

/* here doc */
void	here_doc(t_pipex *p, char **file);

/* utils */
void	ft_free_argv(t_pipex *p);
void	path_search(t_pipex *p, char **envp);
void	openfile(t_pipex *p, char **file, int argc);
int		command_append(t_pipex *p, char *cmd);

/* handle errors */
void	ft_error_msg(char *str);
void	command_not_found(char *cmd);

#endif