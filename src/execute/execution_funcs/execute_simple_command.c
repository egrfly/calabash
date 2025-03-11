/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:47:20 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/11 02:14:29 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include "ft_binary_tree.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../../interface/list_utils/list_utils.h"
#include "../../interface/program_property_utils/program_property_utils.h"
#include "../../parse/tree_node_utils/tree_node_utils.h"
#include "../execute.h"
#include "../builtin_utils/builtin_utils.h"
#include "../command_utils/command_utils.h"
#include "../execution_utils/execution_utils.h"
#include "../redirection_utils/redirection_utils.h"
#include "../var_utils/var_utils.h"
#include "./execution_funcs.h"

static bool	perform_assignments(
				t_list *assignments,
				t_list *vars)
{
	t_list_node	*current_assignment_node;

	current_assignment_node = assignments->first;
	while (current_assignment_node)
	{
		if (!upsert_var(current_assignment_node->value, vars,
				UNCHANGED_OR_NOT_EXPORTED))
			return (false);
		current_assignment_node = current_assignment_node->next;
	}
	return (true);
}

static void	try_execute_as_shell_script(
				char **args,
				char **envp)
{
	size_t	i;
	char	**args_with_program_name;

	i = 1;
	while (args[i - 1])
		i++;
	args_with_program_name = ft_calloc(i + 1, sizeof(char *));
	if (!args_with_program_name)
		return ;
	args_with_program_name[0] = get_program_name();
	i = 1;
	while (args[i - 1])
	{
		args_with_program_name[i] = args[i - 1];
		i++;
	}
	execve(get_program_path(), args_with_program_name, envp);
	free(args_with_program_name);
}

static int	locate_and_execute_command(
				t_binary_tree_node *node,
				t_tokens_and_syntax_tree *tokens_and_syntax_tree,
				t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;
	t_exec_params				exec_params;

	node_value = node->value;
	if (!init_exec_params(&exec_params, node_value->arguments,
			node_value->assignments, program_vars->vars))
		exit_due_to_lack_of_memory(program_vars, &exec_params,
			tokens_and_syntax_tree);
	if (!perform_redirections(node_value->redirections))
		exit_due_to_redirection_failure(program_vars, &exec_params,
			tokens_and_syntax_tree);
	if (!exec_params.path)
		exit_due_to_unfound_command(program_vars, &exec_params,
			tokens_and_syntax_tree, node_value->redirections);
	execve(exec_params.path, exec_params.args, exec_params.envp);
	if (errno == ENOEXEC)
		try_execute_as_shell_script(exec_params.args, exec_params.envp);
	exit_due_to_execve_failure(program_vars, &exec_params,
		tokens_and_syntax_tree, node_value->redirections);
	return (GENERAL_FAILURE);
}

int	execute_simple_command(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;

	node_value = node->value;
	if (node_value->arguments->first)
	{
		if (get_builtin(node_value->arguments->first->value))
			return (execute_builtin(node,
					tokens_and_syntax_tree, program_vars));
		if (node->parent
			&& (node_is_of_type(node->parent->value, PIPE)
				|| node_is_of_type(node->parent->value, PIPE_BOTH)))
			return (locate_and_execute_command(node,
					tokens_and_syntax_tree, program_vars));
		return (execute_in_child_process(locate_and_execute_command, node,
				tokens_and_syntax_tree, program_vars));
	}
	if (!perform_redirections(node_value->redirections))
		return (GENERAL_FAILURE);
	if (!perform_assignments(node_value->assignments, program_vars->vars))
		return (revert_redirections(node_value->redirections), GENERAL_FAILURE);
	return (revert_redirections(node_value->redirections), SUCCESS);
}
