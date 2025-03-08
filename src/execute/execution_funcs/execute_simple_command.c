/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:47:20 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 09:03:56 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_binary_tree.h"
#include "../../interface/interface.h"
#include "../../parse/tree_node_utils/tree_node_utils.h"
#include "../execute.h"
#include "../command_utils/command_utils.h"
#include "../execution_utils/execution_utils.h"
#include "../redirection_utils/redirection_utils.h"

static int	locate_and_execute_command(
				t_binary_tree_node *node,
				t_fixed_program_elements *fixed_program_elements,
				t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;
	t_exec_params				exec_params;

	node_value = node->value;
	if (!init_exec_params(&exec_params, node_value->arguments,
			node_value->assignments, program_vars->env))
		exit_due_to_lack_of_memory(program_vars, &exec_params,
			fixed_program_elements);
	if (!exec_params.path)
		exit_due_to_unfound_command(program_vars, &exec_params,
			fixed_program_elements);
	if (!perform_redirections(node_value->redirections, program_vars->name))
		exit_due_to_redirection_failure(program_vars, &exec_params,
			fixed_program_elements);
	execve(exec_params.path, exec_params.args, exec_params.envp);
	revert_redirections(node_value->redirections);
	exit_due_to_execve_failure(program_vars, &exec_params,
		fixed_program_elements);
	return (GENERAL_FAILURE);
}

// TODO: in the case of assignments and/or redirections only:
// upsert any assignments to local (or to env if already exported)
int	execute_simple_command(
		t_binary_tree_node *node,
		t_fixed_program_elements *fixed_program_elements,
		t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;

	node_value = node->value;
	if (node_value->arguments->first)
	{
		if (node->parent && node_is_of_type(node->parent->value, PIPE))
			return (locate_and_execute_command(node,
					fixed_program_elements, program_vars));
		return (execute_in_child_process(locate_and_execute_command, node,
				fixed_program_elements, program_vars));
	}
	else
	{
		perform_redirections(node_value->redirections, program_vars->name);
		revert_redirections(node_value->redirections);
	}
	return (SUCCESS);
}
