/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:47:24 by gkrusta           #+#    #+#             */
/*   Updated: 2023/08/31 18:34:02 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

void	child_process(int *fd, char **cmd1, char **envp)
{
	if (dup2("infile.txt", STDIN_FILENO) == -1)
		ft_error_msg("Error: ");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_error_msg("Error: ");
	close (fd[0]);
	close ("infile.txt");
	execve();
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	
	if (argc != 5)
		return (1);
	if (open(argv[1], O_RDONLY) == -1)
		return (1);
	if (access(fd[1], R_OK) == -1)
		exit (1);
	pipe(fd);
	pid = fork();
	if (pid == -1)
		return (perror("After creating fork failed. Error: "));
	if (pid == 0) // child process
		child_process(*fd, argv, envp);
	else
		parent_process();
	return (0);
}
