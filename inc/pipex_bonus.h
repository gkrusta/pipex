/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:04:22 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/17 14:54:24 by gkrusta          ###   ########.fr       */
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

/* piping process & forking */
void	pipex_bonus(t_pipex *p, char **argv, char **envp, int argc);


/* here doc */
void	here_doc(t_pipex *p, char **file);

/* utils */
void	ft_error_msg(char *str);
void	ft_free_argv(t_pipex *p);
void	path_search(t_pipex *p, char **envp);
void	openfile(t_pipex *p, char **file, int argc);
int		command_append(t_pipex *p, char *cmd);

#endif