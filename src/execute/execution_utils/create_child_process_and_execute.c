/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_child_process_and_execute.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:11:52 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/15 02:03:42 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "ft_binary_tree.h"
#include "ft_stdio.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../../interface/command_history_utils/command_history_utils.h"
#include "../../interface/program_property_utils/program_property_utils.h"
#include "../../interface/program_vars_lifecycle/program_vars_lifecycle.h"
#include "../execute.h"
#include "./execution_utils.h"

int	create_child_process_and_execute(
		t_execution_func execution_func,
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	int		exit_status;
	pid_t	pid;

	exit_status = SUCCESS;
	pid = fork();
	if (pid == FORK_FAILURE)
		return (ft_dprintf(STDERR_FILENO, "%s: %s: %s\n",
				get_program_name(), "cannot fork", strerror(errno)),
			GENERAL_FAILURE);
	else if (pid == CHILD_PROCESS_ID)
	{
		exit_status = execution_func(node, tokens_and_syntax_tree,
				program_vars);
		destroy_program_vars(program_vars);
		destroy_tokens_and_syntax_tree(tokens_and_syntax_tree);
		clear_command_history();
		exit(exit_status);
	}
	waitpid(pid, &exit_status, NO_OPTIONS);
	return (try_decode_exit_status(exit_status, GENERAL_FAILURE));
}
