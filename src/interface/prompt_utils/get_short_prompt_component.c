/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_short_prompt_component.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 04:25:14 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 04:27:41 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "ft_stdlib.h"
#include "../../main.h"
#include "../../execute/path_utils/path_utils.h"
#include "../../execute/pipeline_utils/pipeline_utils.h"
#include "./prompt_utils.h"

static void	execute_external_command(
				int pipe_fd[2],
				char *command,
				char **argv)
{
	char	*path;

	dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
	close_pipe_fds_for_process((int (*)[2])pipe_fd, SINGLE_PIPE);
	if (!get_full_command_path(&path, command, "/usr/local/bin:/usr/bin:/bin"))
		exit(GENERAL_FAILURE);
	execve(path, argv, (char *[]){NULL});
	exit(GENERAL_FAILURE);
}

void	get_short_prompt_component(
			char *buffer,
			char *command,
			char **argv)
{
	int	pipe_fd[2];
	int	pid;
	int	exit_status;
	int	chars_read;

	buffer[0] = '\0';
	if (pipe(pipe_fd) == PIPE_FAILURE)
		return ;
	pid = fork();
	if (pid == FORK_FAILURE)
	{
		close_pipe_fds_for_process((int (*)[2])pipe_fd, SINGLE_PIPE);
		return ;
	}
	if (pid == CHILD_PROCESS_ID)
		execute_external_command(pipe_fd, command, argv);
	waitpid(pid, &exit_status, NO_OPTIONS);
	if (!WIFEXITED(exit_status) || WEXITSTATUS(exit_status) != SUCCESS)
		return ;
	chars_read = read(pipe_fd[READ_END], buffer, SHORT_PROMPT_COMPONENT_MAX);
	close_pipe_fds_for_process((int (*)[2])pipe_fd, SINGLE_PIPE);
	buffer[ft_max(chars_read, 1) - 1] = '\0';
}
