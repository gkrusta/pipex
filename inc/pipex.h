/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:28:41 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/04 19:17:08 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

# include <fcntl.h>

typedef struct s_pipex {
	int		infile_fd;
	int		outfile_fd;
	int		end[2];
	int		index;
	pid_t	pid1;
	pid_t	pid2;
	char	*cmd;
	char	**path;
	char	**cmd_arg;
}				t_pipex;

/* f */
void	ft_error_msg(char *str);
int		command_append(t_pipex *p, char *cmd);
void	first_child_process(t_pipex *p, char **envp);
void	parent_process(t_pipex *p, char **envp);
void	path_search(t_pipex *p, char **envp);

#endif