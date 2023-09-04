/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:46:13 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/04 19:15:46 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	path_search(t_pipex *p, char **envp)
{
	int		index;
	char	*envp_path;

	index = 0;
	envp_path = 0;
	while (envp[index])
	{
		if (strncmp(envp[index], "PATH=", 5) == 0)
		{
			envp_path = envp[index] + 5;
			break ;
		}
		index++;
	}
	if (!envp_path)
		ft_error_msg("Error: ");
	p->path = ft_split(envp_path, ':');
/* 	int	i = 0;
	while (i < 10)
	{
		printf ("result: %s\n", p->path[i]);
		i++;
	} */
}

void	ft_error_msg(char *str)
{
	perror(str);
	exit (1);
}