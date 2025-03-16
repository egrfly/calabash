/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_conditional_or.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:22:18 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/16 15:21:53 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_tree.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../execute.h"

int	execute_conditional_or(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	int	exit_status;

	exit_status = execute_recursively(node->primary_child,
			tokens_and_syntax_tree, program_vars);
	if (exit_status != SUCCESS && !program_vars->should_exit)
		exit_status = execute_recursively(node->secondary_child,
				tokens_and_syntax_tree, program_vars);
	return (exit_status);
}
