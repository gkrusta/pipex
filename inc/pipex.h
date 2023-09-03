/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:28:41 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/03 19:16:16 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

# include <fcntl.h>

typedef struct s_pipex {
	int		infile_fd;
	int		end[2];
	int		index;
	pid_t	pid;
	char	**cmd;
	char	*path;
}				t_pipex;

/* f */
void	ft_error_msg(char *str);
void	child_process(int infile_fd, char *cmd1, int end[]);
char	*path_search(t_pipex p, char **envp);
char	*command_append(t_pipex p, char *cmd1, char **envp);

#endif