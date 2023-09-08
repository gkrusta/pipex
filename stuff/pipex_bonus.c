/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:03:55 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/08 16:06:12 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	last_child_process(t_pipex *p, char **envp, char *cmd_last)
{
	command_append(p, cmd_last);
	close (p->end[1]);
	if (dup2(p->end[0], STDIN_FILENO) == -1)
		ft_error_msg(" 1 last: ");
	if (dup2(p->outfile_fd, STDOUT_FILENO) == -1)
		ft_error_msg("last: ");
	close (p->end[0]);
	close (p->outfile_fd);
	if (execve(p->cmd, p->cmd_arg, envp) == -1)
	{
		ft_error_msg("Execve: ");
	}
}

void	middle_child(t_pipex *p)
{
	if (dup2(p->end[0], STDIN_FILENO) == -1)
		ft_error_msg("mid: ");
	if (dup2(p->end[1], STDOUT_FILENO) == -1)
		ft_error_msg("2 mid: ");
	close (p->end[0]);
	close (p->end[1]);
}

/* void	openfile(t_pipex *p, char *file)
{
	if (strncmp(file, "here_doc", 9) == 0)
		here_doc(p, file);
	else
		p->infile_fd = open(file, O_RDONLY, 0444);
} */

void	first_child_process(t_pipex *p)
{
	//command_append(p, cmd1);
	close (p->end[0]);
	if (dup2(p->infile_fd, STDIN_FILENO) == -1)
		ft_error_msg("Dup2: ");
	if (dup2(p->end[1], STDOUT_FILENO) == -1)
		ft_error_msg("Dup2: ");
	close (p->end[1]);
	close (p->infile_fd);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*p;
	int		i;
	pid_t	pid;

	p = malloc(sizeof(t_pipex));
	i = 2;
	p->infile_fd = open(argv[1], O_RDONLY, 0444);
	p->outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	//openfile(p, argv[1]);
	//p->outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pipe(p->end);
	path_search(p, envp);
	first_child_process(p);
	int	cmds = argc - 3;
	while (cmds > 0)
	{
		pid = fork();
		if (pid == 0)
		{
			command_append(p, argv[i]);
			if (execve(p->cmd, p->cmd_arg, envp) == -1)
				ft_error_msg("child: ");
		}
		else
		{
			wait(NULL);
			i++;
			if (cmds == 1)
				break ;
			middle_child(p);
		}
		cmds--;
	}
	waitpid(-1, NULL, 0);
	last_child_process(p, envp, argv[argc - 2]);
	puts("end\n");
	ft_free_argv(p);
	return (0);
}
