/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:46:13 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/11 13:02:10 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



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

void	ft_error_msg(char *str)
{
	perror(str);
	exit (1);
}