/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex->c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student->42malaga->com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:47:24 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/04 16:43:21 by gkrusta          ###   ########->fr       */
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
			return (0);
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
	close (p->infile_fd);
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

/* ls -l
split_result = ["ls", "-l", NULL];
arg = ["/bin/ls", "-l", NULL];

arg[0] = "/bin/ls";
arg[1] = "-l"
arg[2] = NULL;
char * const * arg;
execve (arg[0], arg, envp);
 */
//void	processes()

void ft_leaks(void)
 {
    system("leaks -q pipex");
}
int	main(int argc, char **argv, char **envp)
{
	t_pipex	*p;

	atexit(ft_leaks);
/* 	if (argc != 5)
		return (1); */
	(void)argc;
	p = malloc(sizeof(t_pipex));
	p->infile_fd = open(argv[1], O_RDONLY, 0444);
	p->outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->infile_fd == -1 || p->outfile_fd == -1)
		return (1);
	if (access(argv[1], R_OK) == -1 || access(argv[4], W_OK) == -1)
		ft_error_msg("Error: ");
	pipe(p->end);
	path_search(p, envp);
	p->pid1 = fork();
	if (p->pid1 == -1)
		ft_error_msg("Error: ");
	printf("pid 1 is %d\n\n", p->pid1);
	if (p->pid1 == 0) // child process 1 
		first_child_process(p, envp, argv[2]);
	waitpid(p->pid1, NULL, 0);
	p->pid2 = fork();
	printf("pid 2 is %d\n\n", p->pid2);
	if (p->pid1 == -1)
		ft_error_msg("Error: ");
	if (p->pid2 == 0) // child process 2
		second_child_process(p, envp, argv[3]);
	waitpid(p->pid2, NULL, 0);
	printf("pid 1 is %d and pid 2 is %d \n", p->pid1, p->pid2);
	ft_free_argv(p);
/* 	else
	{
		int	*status = 0;
		//wait(NULL)
		//read into the pipe the output of execve
		p->outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (access(argv[4], R_OK) == -1)
			ft_error_msg("Error: ");
		parent_process();
		exit (1);
	} */
/* 	waitpid(p->pid1, &p->status, 0);
	waitpid(p->pid2, &p->status, 0); */
	free(p);
	return (0);
}
