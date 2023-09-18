/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:03:58 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/18 14:41:21 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	second_child_process(t_pipex *p, char **envp, char *cmd2)
{
	waitpid(-1, NULL, 0);
	if (command_append(p, cmd2) == 1)
		command_not_found(cmd2);
	close (p->end[1]);
	if (dup2(p->end[0], STDIN_FILENO) == -1)
		ft_error_msg("Error: ");
	if (dup2(p->outfile_fd, STDOUT_FILENO) == -1)
		ft_error_msg("Error: ");
	close (p->end[0]);
	close (p->outfile_fd);
	if (execve(p->cmd, p->cmd_arg, envp) == -1)
		ft_error_msg("Execve: ");
}

void	first_child_process(t_pipex *p, char **envp, char *cmd1)
{
	if (command_append(p, cmd1) == 1)
		command_not_found(cmd1);
	close (p->end[0]);
	if (dup2(p->infile_fd, STDIN_FILENO) == -1)
		ft_error_msg("Error: ");
	if (dup2(p->end[1], STDOUT_FILENO) == -1)
		ft_error_msg("Error: ");
	close (p->end[1]);
	close (p->infile_fd);
	if (execve(p->cmd, p->cmd_arg, envp) == -1)
		ft_error_msg("Execve: ");
}

void	pipex(t_pipex *p, char **cmd, char **envp)
{
	if (access(cmd[1], R_OK) == -1 || access(cmd[4], W_OK) == -1)
		ft_error_msg("Error: ");
	pipe(p->end);
	p->pid1 = fork();
	if (p->pid1 == -1)
		ft_error_msg("Error: ");
	if (p->pid1 == 0)
		first_child_process(p, envp, cmd[2]);
	waitpid(p->pid1, NULL, WNOHANG);
	p->pid2 = fork();
	if (p->pid2 == -1)
		ft_error_msg("Error: ");
	if (p->pid2 == 0)
		second_child_process(p, envp, cmd[3]);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*p;

	if (argc != 5)
		exit(1);
	else
	{
		p = malloc(sizeof(t_pipex));
		openfile(p, argv);
		path_search(p, envp);
		pipex(p, argv, envp);
		waitpid(-1, NULL, 0);
		ft_free_argv(p);
	}
	return (0);
}
