/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:03:58 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/17 21:04:45 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	openfile(t_pipex *p, char **file, int argc)
{
	if (strncmp(file[1], "here_doc", 9) == 0)
	{
		here_doc(p, file);
		if (dup2(p->end[0], STDIN_FILENO) == -1)
			ft_error_msg("Dup2: ");
		close (p->end[0]);
		p->i = 3;
	}
	else
	{
		p->infile_fd = open(file[1], O_RDONLY, 0444);
		if (dup2(p->infile_fd, STDIN_FILENO) == -1)
			ft_error_msg("Dup2: ");
		close (p->infile_fd);
		p->i = 2;
	}
	p->outfile_fd = open(file[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

int	command_append(t_pipex *p, char *cmd)
{
	int		index;
	char	*cmd_with_slash;
	//char	*saver;

	index = -1;
	p->cmd_arg = ft_split(cmd, ' ');
	cmd_with_slash = ft_strjoin("/", p->cmd_arg[0]);
	while (p->path[++index])
	{
		//saver = p->path[index];
		p->cmd = ft_strjoin(p->path[index], cmd_with_slash);
		if (access(p->cmd, X_OK) == 0)
			return (0);
		//free(saver);
	}
	return (1);
}

void	path_search(t_pipex *p, char **envp)
{
	char	*envp_path;

	p->index = 0;
	envp_path = 0;
	while (envp[p->index])
	{
		if (strncmp(envp[p->index], "PATH=", 5) == 0)
		{
			envp_path = envp[p->index] + 5;
			break ;
		}
		p->index++;
	}
	if (!envp_path)
		ft_error_msg("Error: ");
	p->path = ft_split(envp_path, ':');
}

void	ft_free_argv(t_pipex *p)
{
	while (p->index-- > 0)
		free (p->path[p->index]);
	free (p->path);
	free (p);
}
