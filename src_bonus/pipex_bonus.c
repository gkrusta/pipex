/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:03:55 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/07 16:41:45 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"


void	last_child_process(t_pipex *p, char **envp, char *cmd2)
{
	waitpid(-1, NULL, 0);
	command_append(p, cmd2);
	close (p->end[1]);
	if (dup2(p->end[0], STDIN_FILENO) == -1)
		ft_error_msg("Error: ");
	if (d000up2(p->outfile_fd, STDOUT_FILENO) == -1)
		ft_error_msg("Error: ");
	close (p->end[0]);
	close (p->outfile_fd);
	if (execve(p->cmd, p->cmd_arg, envp) == -1)
	{
		ft_error_msg("Execve: ");
	}
}

void	first_child_process(t_pipex *p, char **envp, char *cmd1)
{
	command_append(p, cmd1);
	close (p->end[0]);
	//if argv[1] its not here__doc ->
	if (dup2(p->infile_fd, STDIN_FILENO) == -1)
		ft_error_msg("Error: ");
	if (dup2(p->end[1], STDOUT_FILENO) == -1)
		ft_error_msg("Error: ");
	close (p->end[1]);
	close (p->infile_fd);
	if (execve(p->cmd, p->cmd_arg, envp) == -1)
	{
		ft_error_msg("Execve: ");
	}
}

void	middle_child(t_pipex *p, char **envp, char *cmd, pid_t prev_id)
{
	waitpid(prev_id, NULL, 0);
	command_append(p, cmd);
	if (dup2(p->end[1], STDIN_FILENO) == -1)
		ft_error_msg("Error: ");
	if (dup2(p->end[0], STDOUT_FILENO) == -1)
		ft_error_msg("Error: ");
	close (p->end[0]);
	//close (p->end[1]);
	if (execve(p->cmd, p->cmd_arg, envp) == -1)
	{
		ft_error_msg("Execve: ");
	}
}

void	pipex(t_pipex *p, char **cmd, char **envp)
{
	if (p->infile_fd == -1 || p->outfile_fd == -1)
		ft_error_msg("Error: ");
	if (access(cmd[1], R_OK) == -1 || access(cmd[4], W_OK) == -1)
		ft_error_msg("Error: ");
	pipe(p->end);
	p->pid1 = fork();
	if (p->pid1 == -1)
		ft_error_msg("Error: ");
	printf("pid 1 is %d\n\n", p->pid1);
	if (p->pid1 == 0) // child process 1 
		first_child_process(p, envp, cmd[2]);
	waitpid(p->pid1, NULL, WNOHANG);
	p->pid2 = fork();
	printf("pid 2 is %d\n\n", p->pid2);
	if (p->pid1 == -1)
		ft_error_msg("Error: ");
	if (p->pid2 == 0) // child process 2
		second_child_process(p, envp, cmd[3]);
}

void	openfile(t_pipex *p, char *file)
{
	if (strncmp(file, "here_doc", 9) == 0)
		here_doc(p, file);
	else
		p->infile_fd = open(file[1], O_RDONLY, 0444);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*p;

	p = malloc(sizeof(t_pipex));
	p->pipes = argc - 3;
	openfile(p, argv[1]);
	p->outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	path_search(p, envp);
	pipex(p, argv, envp);
	waitpid(-1, NULL, 0);
	puts("end\n");
	ft_free_argv(p);
	return (0);
}
