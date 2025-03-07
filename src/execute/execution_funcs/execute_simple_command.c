/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:47:20 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/07 08:35:47 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_binary_tree.h"
#include "../../interface/interface.h"
#include "../../parse/tree_node_utils/tree_node_utils.h"
#include "../execute.h"
#include "../command_utils/command_utils.h"
#include "../execution_utils/execution_utils.h"
#include "../builtins/builtins.h"
#include "../list_utils/list_utils.h"

static int	locate_and_execute_command(
				t_binary_tree_node *node,
				t_tokens_and_syntax_tree *tokens_and_syntax_tree,
				t_program_name_and_env *program_name_and_env)
{
	t_syntax_tree_node_value	*node_value;
	t_exec_params				exec_params;

	node_value = node->value;
	if (!init_exec_params(&exec_params, node_value->arguments,
			program_name_and_env->env))
		exit_due_to_lack_of_memory(program_name_and_env->name, &exec_params,
			tokens_and_syntax_tree);
	if (!exec_params.path)
		exit_due_to_unfound_command(program_name_and_env->name,
			node_value->arguments->first->value, &exec_params,
			tokens_and_syntax_tree);
	execve(exec_params.path, exec_params.args, exec_params.envp);
	exit_due_to_execve_failure(program_name_and_env->name,
		node_value->arguments->first->value, &exec_params,
		tokens_and_syntax_tree);
	return (GENERAL_FAILURE);
}

// TODO: figure out what to do in the case of assignments and redirections only
// TODO: Atti - execute_builtin_command - will probably need changing to be
//				able to handle recursive execution?
int	execute_simple_command(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_name_and_env *program_name_and_env)
{
	t_syntax_tree_node_value	*node_value;

	node_value = node->value;
	if (node_value->arguments->first)
	{
		if (is_builtin_command(node_value->arguments->first->value))
			return (execute_builtin_command(
					node_value->arguments->first->value,
					(const char **)get_values_from_list(node_value->arguments),
					program_name_and_env));
		if (node->parent && node_is_of_type(node->parent->value, PIPE))
			return (locate_and_execute_command(node,
					tokens_and_syntax_tree, program_name_and_env));
		return (execute_in_child_process(locate_and_execute_command, node,
				tokens_and_syntax_tree, program_name_and_env));
	}
	return (SUCCESS);
}
