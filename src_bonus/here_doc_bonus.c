/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:18:41 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/18 14:34:00 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(t_pipex *p, char **file)
{
	char	*limiter;
	char	*line;

	limiter = file[2];
	pipe(p->end);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 10)
		{
			free (line);
			break ;
		}
		write (p->end[1], line, ft_strlen(line));
		free (line);
	}
	close (p->end[1]);
}
