/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_in_child_process.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:11:52 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/07 04:18:52 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "ft_binary_tree.h"
#include "ft_stdio.h"
#include "../../interface/interface.h"
#include "../execute.h"
#include "./execution_utils.h"

int	execute_in_child_process(
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
				program_vars->name, "cannot fork", strerror(errno)),
			GENERAL_FAILURE);
	else if (pid == CHILD_PROCESS_ID)
	{
		exit_status = execution_func(node, tokens_and_syntax_tree,
				program_vars);
		destroy_tokens_and_syntax_tree(tokens_and_syntax_tree);
		exit(exit_status);
	}
	waitpid(pid, &exit_status, NO_OPTIONS);
	return (exit_status);
}
