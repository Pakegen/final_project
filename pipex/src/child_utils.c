/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 14:08:21 by qacjl             #+#    #+#             */
/*   Updated: 2025/01/16 22:45:00 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_child(int input_fd, int output_fd, char *cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit("ERROR FORK");
	if (pid == 0)
	{
		redirect(input_fd, output_fd);
		run_command(cmd, env);
	}
}

void	redirect(int input_fd, int output_fd)
{
	int	dup_in;
	int	dup_out;

	dup_in = dup2(input_fd, STDIN_FILENO);
	dup_out = dup2(output_fd, STDOUT_FILENO);
	if (dup_in == -1 || dup_out == -1)
		error_exit("ERROR: ECHEC IN THE REDIRECTION\n");
	close(input_fd);
	close(output_fd);
}

void	wait_for_all_children(void)
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			ft_putendl_fd("WARNING PROCESS FAILED\n", 2);
		pid = wait(&status);
	}
}

void	run_command(char *cmd, char **env)
{
	char	**args;
	char	*resolved_cmd;

	if (!cmd || cmd[0] == '\0')
		error_exit("ERROR: Invalid command\n");
	args = ft_split(cmd, ' ');
	if (!args || !args[0])
		error_exit("ERROR: Failed to parse command\n");
	resolved_cmd = find_command_path(args[0], env);
	if (!resolved_cmd)
	{
		ft_putstr_fd("ERROR: Command not found: ", 2);
		ft_putendl_fd(args[0], 2);
		free_split(args);
		exit(127);
	}
	execve(resolved_cmd, args, env);
	error_exit("ERROR: Failed to execute command\n");
}
