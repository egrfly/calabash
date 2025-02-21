/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_slot_new_node_between_current_node_par        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 01:04:14 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/20 22:16:37 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"
#include "../tree_node_lifecycle/tree_node_lifecycle.h"

void	undo_slot_new_node_between_current_secondary_child_and_parent(
			t_syntax_tree *syntax_tree)
{
	t_binary_tree_node	*new_node;

	new_node = syntax_tree->current_node->parent;
	new_node->parent->secondary_child = syntax_tree->current_node;
	syntax_tree->current_node->parent = new_node->parent;
	destroy_syntax_tree_node(new_node);
}
