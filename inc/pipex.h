/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:28:41 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/17 21:03:43 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

typedef struct s_pipex {
	int		infile_fd;
	int		outfile_fd;
	int		status;
	int		end[2];
	int		index;
	pid_t	pid1;
	pid_t	pid2;
	char	*cmd;
	char	**path;
	char	**cmd_arg;
}				t_pipex;

/* piping process & forking */
void	pipex(t_pipex *p, char **cmd, char **envp);
void	first_child_process(t_pipex *p, char **envp, char *cmd1);
void	second_child_process(t_pipex *p, char **envp, char *cmd2);

/* utils */
int		command_append(t_pipex *p, char *cmd);
void	path_search(t_pipex *p, char **envp);
void	openfile(t_pipex *p, char **file);
void	ft_free_argv(t_pipex *p);

/* handle errors */
void	ft_error_msg(char *str);
void	command_not_found(char *cmd);

#endif