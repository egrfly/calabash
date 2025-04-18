/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_conditional_and.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:22:18 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/16 16:08:21 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_tree.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../execute.h"
#include "../execution_utils/execution_utils.h"

int	execute_conditional_and(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	int	exit_status;

	exit_status = execute_recursively(node->primary_child,
			tokens_and_syntax_tree, program_vars);
	update_last_exit_status(exit_status, program_vars);
	if (exit_status == SUCCESS && !program_vars->should_exit)
		exit_status = execute_recursively(node->secondary_child,
				tokens_and_syntax_tree, program_vars);
	return (exit_status);
}
