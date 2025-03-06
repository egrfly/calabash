/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_conditional_and.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:22:18 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/05 21:28:46 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_tree.h"
#include "../../interface/interface.h"
#include "../execute.h"

int	execute_conditional_and(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_name_and_env *program_name_and_env)
{
	int	exit_status;

	exit_status = execute_recursively(node->primary_child,
			tokens_and_syntax_tree, program_name_and_env);
	if (exit_status == SUCCESS)
		exit_status = execute_recursively(node->secondary_child,
				tokens_and_syntax_tree, program_name_and_env);
	return (exit_status);
}
