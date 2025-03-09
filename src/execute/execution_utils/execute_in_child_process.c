/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_in_child_process.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:11:52 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/09 17:15:03 by aistok           ###   ########.fr       */
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
#include "../../interface/program_name_utils/program_name_utils.h"
#include "../../interface/program_vars_lifecycle/program_vars_lifecycle.h"
#include "../execute.h"
#include "./execution_utils.h"

int	execute_in_child_process(
		t_execution_func execution_func,
		t_binary_tree_node *node,
		t_fixed_program_elements *fixed_program_elements,
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
		exit_status = execution_func(node, fixed_program_elements,
				program_vars);
		destroy_program_vars(program_vars);
		destroy_fixed_program_elements(fixed_program_elements);
		exit(exit_status);
	}
	waitpid(pid, &exit_status, NO_OPTIONS);
	return (try_decode_exit_status(exit_status, GENERAL_FAILURE));
}
