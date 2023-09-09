/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:03:55 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/09 20:03:03 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	last_process(t_pipex *p, char **envp, char *cmd_last)
{
	command_append(p, cmd_last);
	close (p->end[0]);
	if (dup2(p->outfile_fd, STDOUT_FILENO) == -1)
		ft_error_msg("last: ");
	close (p->end[1]);
	close (p->outfile_fd);
	if (execve(p->cmd, p->cmd_arg, envp) == -1)
	{
		ft_error_msg("Execve: ");
	}
}

void	middle_child(t_pipex *p)
{
	close (p->end[1]);
	if (dup2(p->end[0], STDIN_FILENO) == -1)
		ft_error_msg("mid: ");
}

/* void	openfile(t_pipex *p, char *file)
{
	if (strncmp(file, "here_doc", 9) == 0)
		here_doc(p, file);
	else
		p->infile_fd = open(file, O_RDONLY, 0444);
} */

/* void	first_child_process(t_pipex *p)
{
	//command_append(p, cmd1);
	close (p->end[0]);
	if (dup2(p->infile_fd, STDIN_FILENO) == -1)
		ft_error_msg("Dup2: ");
	if (dup2(p->end[1], STDOUT_FILENO) == -1)
		ft_error_msg("Dup2: ");
	close (p->end[1]);
	close (p->infile_fd);
} */

void	ft_leaks(void)
{
	system("leaks -q pipex_bonus");
}


int	main(int argc, char **argv, char **envp)
{
	t_pipex	*p;
	int		i;
	pid_t	pid;

	atexit(ft_leaks);
	p = malloc(sizeof(t_pipex));
	if (argc > 4)
	{
		i = 2;
		p->infile_fd = open(argv[1], O_RDONLY, 0444);
		p->outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		//openfile(p, argv[1]);
		path_search(p, envp);
		if (dup2(p->infile_fd, STDIN_FILENO) == -1)
			ft_error_msg("Dup2: ");
		close (p->infile_fd);
		int	cmds = argc - 3;
		while (--cmds > 0)
		{
			pipe(p->end);
			pid = fork();
			printf("pid is %d\n", pid);
			if (pid == 0)
			{
				command_append(p, argv[++i]);
				puts("after append\n");
				close (p->end[0]);
				if (dup2(p->end[1], STDOUT_FILENO) == -1)
					ft_error_msg("Dup2: ");
				if (execve(p->cmd, p->cmd_arg, envp) == -1)
					ft_error_msg("child: ");
			}
			else
			{
				///wait(NULL);
				waitpid(pid, NULL, 0);
				puts("end\n");
				middle_child(p);
			}
		}
	//wait(NULL);
	//waitpid(-1, NULL, 0);
	last_process(p, envp, argv[argc - 2]);
	//waitpid(pid, NULL, 0);
	puts("end\n");
	}
	ft_free_argv(p);
	return (0);
}



/* Child process that create a fork and a pipe, put the output inside a pipe
 and then close with the exec function. The main process will change his stdin
 for the pipe file descriptor. */
/* void	child_process(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
} */

/* Function who make a child process that will read from the stdin with
 get_next_line until it find the limiter word and then put the output inside a
 pipe. The main process will change his stdin for the pipe file descriptor. */
/* void	here_doc(char *limiter, int argc)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (argc < 6)
		usage();
	if (pipe(fd) == -1)
		error();
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
} */

/* Main function that run the childs process with the right file descriptor
 or display an error message if arguments are wrong. It will run here_doc
 function if the "here_doc" string is find in argv[1] */
/* int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	filein;
	int	fileout;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			fileout = open_file(argv[argc - 1], 0);
			here_doc(argv[2], argc);
		}
		else
		{
			i = 2;
			fileout = open_file(argv[argc - 1], 1);
			filein = open_file(argv[1], 2);
			dup2(filein, STDIN_FILENO);
		}
		while (i < argc - 2)
			child_process(argv[i++], envp);
		dup2(fileout, STDOUT_FILENO);
		execute(argv[argc - 2], envp);
	}
	usage();
} */