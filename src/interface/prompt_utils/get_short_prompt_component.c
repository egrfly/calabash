/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_short_prompt_component.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 04:25:14 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/19 17:54:15 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "ft_stdlib.h"
#include "../../main.h"
#include "../../execute/execution_utils/execution_utils.h"
#include "../../execute/path_utils/path_utils.h"
#include "../../execute/pipeline_utils/pipeline_utils.h"
#include "../command_history_utils/command_history_utils.h"
#include "../program_property_utils/program_property_utils.h"
#include "../program_vars_lifecycle/program_vars_lifecycle.h"
#include "./prompt_utils.h"

void	get_short_prompt_component(
			char *buffer,
			char **argv,
			t_program_vars *program_vars)
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
		execute_external_command(pipe_fd, argv, program_vars, NO_ARG);
	waitpid(pid, &exit_status, NO_OPTIONS);
	if (!WIFEXITED(exit_status) || WEXITSTATUS(exit_status) != SUCCESS)
		return ;
	chars_read = read(pipe_fd[READ_END], buffer, SHORT_PROMPT_COMPONENT_MAX);
	close_pipe_fds_for_process((int (*)[2])pipe_fd, SINGLE_PIPE);
	buffer[ft_max(chars_read - 1, 0)] = '\0';
}
