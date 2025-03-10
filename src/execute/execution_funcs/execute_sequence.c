/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_sequence.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:23:52 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 05:57:07 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_tree.h"
#include "../../interface/interface.h"
#include "../execute.h"

int	execute_sequence(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	return (execute_recursively(node->primary_child, tokens_and_syntax_tree,
			program_vars),
		execute_recursively(node->secondary_child, tokens_and_syntax_tree,
			program_vars));
}
