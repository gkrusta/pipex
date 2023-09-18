/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:39:10 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/18 15:11:36 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	parent_process(t_pipex *p)
{
	close (p->end[1]);
	if (dup2(p->end[0], STDIN_FILENO) == -1)
		ft_error_msg("dup2: ");
}

void	last_process(t_pipex *p, char **envp, char *cmd_last)
{
	p->pid = fork();
	if (p->pid == 0)
	{
		if (command_append(p, cmd_last) == 1)
			command_not_found(cmd_last);
		close (p->end[0]);
		if (dup2(p->outfile_fd, STDOUT_FILENO) == -1)
			ft_error_msg("dup2: ");
		close (p->outfile_fd);
		if (execve(p->cmd, p->cmd_arg, envp) == -1)
			ft_error_msg("Execve: ");
	}
	else
	{
		waitpid(p->pid, NULL, WNOHANG);
		parent_process(p);
	}
}

void	pipex_bonus(t_pipex *p, char **argv, char **envp, int argc)
{
	while (p->i < argc - 2)
	{
		pipe(p->end);
		p->pid = fork();
		if (p->pid == -1)
			ft_error_msg("pid: ");
		if (p->pid == 0)
		{
			if (command_append(p, argv[p->i]) == 1)
				command_not_found(argv[p->i]);
			close (p->end[0]);
			if (dup2(p->end[1], STDOUT_FILENO) == -1)
				ft_error_msg("dup2: ");
			if (execve(p->cmd, p->cmd_arg, envp) == -1)
				ft_error_msg("Execve: ");
		}
		else
		{
			waitpid(p->pid, NULL, WNOHANG);
			parent_process(p);
		}
		p->i++;
	}
	waitpid(-1, NULL, 0);
	last_process(p, envp, argv[argc -2]);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*p;

	if (argc > 5)
	{
		p = malloc(sizeof(t_pipex));
		openfile(p, argv, argc);
		path_search(p, envp);
		pipex_bonus(p, argv, envp, argc);
		waitpid(-1, NULL, 0);
		ft_free_argv(p);
	}
	return (0);
}
