/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:46:13 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/13 09:23:14 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	command_append(t_pipex *p, char *cmd)
{
	int		index;
	char	*cmd_with_slash;
	char	*saver;

	index = -1;
	p->cmd_arg = ft_split(cmd, ' ');
	cmd_with_slash = ft_strjoin("/", p->cmd_arg[0]);
	free(cmd_with_slash);
	while (p->path[++index])
	{
		p->cmd = ft_strjoin(p->path[index], cmd_with_slash);
		saver = p->cmd;
		if (access(p->cmd, X_OK) == 0)
			return (0);
		free(saver);
	}
	return (1);
}

void	path_search(t_pipex *p, char **envp)
{
	char	*envp_path;
	int		i;

	i = 0;
	envp_path = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			envp_path = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!envp_path)
		ft_error_msg("Error: ");
	p->path = ft_split(envp_path, ':');
}

void	ft_free_argv(t_pipex *p)
{
	int	i;

	i = 0;
	while (p->path[i])
	{
		free(p->path[i]);
		i++;
	}
	free (p->path);
	i = 0;
	while (p->cmd_arg)
	{
		free(p->cmd_arg[i]);
		i++;
	}
	free (p->cmd_arg);
	free (p);
}

void	ft_error_msg(char *str)
{
	perror(str);
	exit (1);
}