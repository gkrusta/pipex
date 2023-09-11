/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:04:22 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/11 12:10:43 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"

typedef struct s_pipex {
	int		infile_fd;
	int		outfile_fd;
	int		status;
	int		end[2];
	int		index;
	int		i;
	int		cmds;
	char	*cmd;
	char	**path;
	char	**cmd_arg;
}				t_pipex;

/* utils */
void	ft_error_msg(char *str);
void	ft_free_argv(t_pipex *p);
void	path_search(t_pipex *p, char **envp);


int		command_append(t_pipex *p, char *cmd);

/* here doc */
void	here_doc(t_pipex *p, char **file);

#endif