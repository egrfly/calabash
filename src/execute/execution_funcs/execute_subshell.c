/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:25:48 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/26 22:28:14 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_tree.h"
#include "../../main.h"
#include "../../expand/expand.h"
#include "../../interface/interface.h"
#include "../execute.h"
#include "../command_utils/command_utils.h"
#include "../execution_utils/execution_utils.h"
#include "../redirection_utils/redirection_utils.h"

static int	execute_recursively_with_redirections(
				t_binary_tree_node *node,
				t_tokens_and_syntax_tree *tokens_and_syntax_tree,
				t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;
	int							exit_status;

	node_value = node->value;
	if (!expand_redirection_right_words(node_value->redirections, program_vars)
		|| !perform_redirections(node_value->redirections))
		return (GENERAL_FAILURE);
	exit_status = execute_recursively(node, tokens_and_syntax_tree,
			program_vars);
	revert_redirections(node_value->redirections);
	return (exit_status);
}

int	execute_subshell(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	return (create_child_process_and_execute(
			execute_recursively_with_redirections, node->primary_child,
			tokens_and_syntax_tree, program_vars));
}
