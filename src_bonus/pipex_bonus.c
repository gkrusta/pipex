/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:03:55 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/17 21:16:56 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	middle_child(t_pipex *p)
{
	close (p->end[1]);
	if (dup2(p->end[0], STDIN_FILENO) == -1)
		ft_error_msg("dup2: ");
}

void	last_process(t_pipex *p, char **envp, char *cmd_last)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
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
		waitpid(pid, NULL, WNOHANG);
		middle_child(p);
	}
}

/* void	ft_leaks(void)
{
	system("leaks -q pipex_bonus");
} */


//--- test ---
void	last_process(t_pipex *p, char **envp, char *cmd_last)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
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
		waitpid(pid, NULL, WNOHANG);
		middle_child(p);
	}
}
///-------


void	pipex_bonus(t_pipex *p, char **argv, char **envp, int argc)
{
	pid_t	pid;

	while (p->i < argc - 2)
	{
		pipe(p->end);
		pid = fork();
		if (pid == -1)
			ft_error_msg("pid: ");
		if (pid == 0)
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
			waitpid(pid, NULL, WNOHANG);
			middle_child(p);
		}
		p->i++;
	}
	waitpid(-1, NULL, 0);
	last_process(p, envp, argv[argc -2]);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*p;

	//atexit(ft_leaks);

	p = malloc(sizeof(t_pipex));
	if (argc > 4)
	{
		openfile(p, argv, argc);
		path_search(p, envp);
		pipex_bonus(p, argv, envp, argc);
		waitpid(-1, NULL, 0);
	}
	ft_free_argv(p);
	return (0);
}
