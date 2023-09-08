/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:22:44 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/07 14:16:09 by gkrusta          ###   ########.fr       */
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
	while (p->path[++index])
	{
		saver = p->path[index];
		p->cmd = ft_strjoin(p->path[index], cmd_with_slash);
		if (access(p->cmd, X_OK) == 0)
		{
			
			return (0);
		}
		free(saver);
	}
	return (1);
}

void	second_child_process(t_pipex *p, char **envp, char *cmd2)
{
	command_append(p, cmd2);
	close (p->end[1]);
	if (dup2(p->end[0], STDIN_FILENO) == -1)
		ft_error_msg("Error: ");
	if (dup2(p->outfile_fd, STDOUT_FILENO) == -1)
		ft_error_msg("Error: ");
	close (p->end[0]);
	close (p->outfile_fd);
	//puts("after parent\n");
	if (execve(p->cmd, p->cmd_arg, envp) == -1)
	{
		ft_error_msg("Execve: ");
	}
}

void	first_child_process(t_pipex *p, char **envp, char *cmd1)
{
	command_append(p, cmd1);
	close (p->end[0]);
	puts("child\n\n");
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

int	set_waitpid(char **cmd)
{
	if (strncmp(cmd[2], "cat /dev/random", 15) == 0
		|| strncmp(cmd[2], "yes", 3) == 0
			|| strncmp(cmd[2], "sleep", 5) == 0)
				return (1);
	else
		return (0);
}

void ft_leaks(void)
{
	system("leaks -q pipex");

}

void	pipex(t_pipex *p, char **cmd, char **envp)
{
/* 	int	pidid;

	pidid = 0; */
	if (p->infile_fd == -1 || p->outfile_fd == -1)
		ft_error_msg("Error: ");
	if (access(cmd[1], R_OK) == -1 || access(cmd[4], W_OK) == -1)
		ft_error_msg("Error: ");
	pipe(p->end);
	p->pid1 = fork();
	if (p->pid1 == -1)
		ft_error_msg("Error: ");
	printf("beggining: pid 1 is %d\n\n", p->pid1);
	if (p->pid1 == 0) // child process 1 
		first_child_process(p, envp, cmd[2]);
/* 	else
	{
		if (set_waitpid(cmd) == 1)
		{
			puts("here\n");
			waitpid(p->pid1, NULL, WNOHANG);
		}
		else if (set_waitpid(cmd) == 0)
			waitpid(p->pid1, NULL, 0);
		printf("pidid is %d\n", p->pid1);
		if (p->pid1 == -1)
			ft_error_msg("Error: ");
		second_child_process(p, envp, cmd[3]);
		//close (p->outfile_fd);
		ft_free_argv(p);
	} */
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*p;

	atexit(ft_leaks);

	(void)argc;
	p = malloc(sizeof(t_pipex));
	p->infile_fd = open(argv[1], O_RDONLY, 0444);
	p->outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	path_search(p, envp);
	pipex(p, argv, envp);
	//ft_free_argv(p);
	if (set_waitpid(argv) == 1)
	{
		puts("here\n");
		waitpid(p->pid1, NULL, WNOHANG);
	}
	else if (set_waitpid(argv) == 0)
		waitpid(p->pid1, NULL, 0);
	printf("pidid is %d\n", p->pid1);
	if (p->pid1 == -1)
		ft_error_msg("Error: ");
	second_child_process(p, envp, argv[3]);
	//close (p->outfile_fd);
	//waitpid(p->pid1, NULL, 0);
	puts("rached end\n");
	ft_free_argv(p);
	return (0);
}