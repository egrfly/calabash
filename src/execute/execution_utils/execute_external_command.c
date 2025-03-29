/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:50:36 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/19 17:53:02 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../../main.h"
#include "../../interface/command_history_utils/command_history_utils.h"
#include "../../interface/program_vars_lifecycle/program_vars_lifecycle.h"
#include "../path_utils/path_utils.h"
#include "../pipeline_utils/pipeline_utils.h"
#include "./execution_utils.h"

void	execute_external_command(
			int pipe_fd[2],
			char **argv,
			t_program_vars *program_vars,
			t_tokens_and_syntax_tree *tokens_and_syntax_tree)
{
	char	*path;

	dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
	close_pipe_fds_for_process((int (*)[2])pipe_fd, SINGLE_PIPE);
	if (get_full_command_path(&path, argv[0], "/usr/local/bin:/usr/bin:/bin"))
		execve(path, argv, (char *[]){NULL});
	destroy_program_vars(program_vars);
	destroy_tokens_and_syntax_tree(tokens_and_syntax_tree);
	clear_command_history();
	exit(GENERAL_FAILURE);
}
