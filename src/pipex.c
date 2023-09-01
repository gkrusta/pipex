/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:47:24 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/01 17:23:02 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**path_search(char * command, char ** envp) {
	char ** split_result;
	unsigned int index = 0;
	char * path;

	envp == char **
	envp[index] == char *
	while (envp[index]) {
		if (envp[index] == "PATH=")
		{
			path = envp[index];
			break ;
		}
		index++;
	}
	path = substr (6, path, strlen(path));
a
	index = 0;
	split_result = split (path,':')
	char * command_with_slash = strjoin ("/", command );
	char * saver;
	while (split_result[index])
	{
		//memory leaks
		saver = split_result[index];
		
		split_result[index] = strjoin (split_result[index], command_with_slash);
		
		free (saver);
		index++;
	}
}

void	child_process(int infile_fd, char *cmd1, int end[])
{
	(void)cmd1;
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		ft_error_msg("Error: ");
	if (dup2(end[1], STDOUT_FILENO) == -1)
		ft_error_msg("Error: ");
	close (end[0]);
	close (infile_fd);
	while (split_result[index])
	{	
		execve();
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		infile_fd;
	int		end[2];
	//int		fd2;
	pid_t	pid;
	
	(void)envp;
	if (argc != 5)
		return (1);
	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
		return (1);
	if (access(argv[1], R_OK) == -1)
		exit (1);
	pipe(end);
	pid = fork();
	if (pid == -1)
		ft_error_msg("Error: ");
	//if (pid == 0) // child process
		child_process(infile_fd, argv[2], end);
/* 	else
		parent_process(); */
	return (0);
}
