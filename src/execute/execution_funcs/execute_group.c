/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_group.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:24:48 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 09:44:50 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_tree.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../execute.h"
#include "../command_utils/command_utils.h"
#include "../redirection_utils/redirection_utils.h"

int	execute_group(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;
	int							exit_status;

	node_value = node->value;
	if (!perform_redirections(node_value->redirections))
		exit_due_to_redirection_failure(program_vars, NO_ARG,
			tokens_and_syntax_tree);
	exit_status = execute_recursively(node->primary_child,
			tokens_and_syntax_tree, program_vars);
	revert_redirections(node_value->redirections);
	return (exit_status);
}
