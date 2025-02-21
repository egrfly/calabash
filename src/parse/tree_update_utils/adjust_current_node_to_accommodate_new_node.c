/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_current_node_to_accommodate_new_node        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:43:21 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 06:03:06 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_binary_tree.h"
#include "ft_list.h"
#include "../parse.h"
#include "../tree_node_lifecycle/tree_node_lifecycle.h"
#include "../tree_node_utils/tree_node_utils.h"
#include "../tree_undo_action_funcs/tree_undo_action_funcs.h"
#include "./tree_update_utils.h"

static bool	slot_into_root_of_syntax_tree(
				t_binary_tree_node *new_node,
				t_syntax_tree *syntax_tree)
{
	if (!ft_list_append(syntax_tree->undo_actions,
			undo_set_tree_root_and_current_node_to_new_non_null_node))
		return (destroy_syntax_tree_node(new_node), false);
	syntax_tree->tree->root = new_node;
	syntax_tree->current_node = new_node;
	return (true);
}

static bool	slot_into_primary_child_of_current_node(
				t_binary_tree_node *new_node,
				t_syntax_tree *syntax_tree)
{
	if (!ft_list_append(syntax_tree->undo_actions,
			undo_set_current_node_to_new_non_null_primary_child))
		return (destroy_syntax_tree_node(new_node), false);
	syntax_tree->current_node->primary_child = new_node;
	new_node->parent = syntax_tree->current_node;
	syntax_tree->current_node = syntax_tree->current_node->primary_child;
	return (true);
}

static bool	slot_into_secondary_child_of_current_node(
				t_binary_tree_node *new_node,
				t_syntax_tree *syntax_tree)
{
	if (!ft_list_append(syntax_tree->undo_actions,
			undo_set_current_node_to_new_non_null_secondary_child))
		return (destroy_syntax_tree_node(new_node), false);
	syntax_tree->current_node->secondary_child = new_node;
	new_node->parent = syntax_tree->current_node;
	syntax_tree->current_node = syntax_tree->current_node->secondary_child;
	return (true);
}

static bool	slot_into_secondary_child_of_new_sequence_node(
				t_binary_tree_node *new_node,
				t_syntax_tree *syntax_tree)
{
	if (!slot_new_node_up_tree_between_nodes_of_suitable_precedences(SEQUENCE,
			syntax_tree))
		return (destroy_syntax_tree_node(new_node), false);
	if (!ft_list_append(syntax_tree->undo_actions,
			undo_set_current_node_to_new_secondary_child_sibling))
		return (destroy_syntax_tree_node(new_node), false);
	new_node->parent = syntax_tree->current_node->parent;
	syntax_tree->current_node->parent->secondary_child = new_node;
	syntax_tree->current_node
		= syntax_tree->current_node->parent->secondary_child;
	return (true);
}

bool	adjust_current_node_to_accommodate_new_node(
			t_syntax_tree_node_value_type new_node_value_type,
			t_syntax_tree *syntax_tree)
{
	t_binary_tree_node	*new_node;

	new_node = create_syntax_tree_node(new_node_value_type);
	if (!new_node)
		return (false);
	if (!syntax_tree->current_node)
		return (slot_into_root_of_syntax_tree(new_node,
				syntax_tree));
	else if ((node_is_of_a_single_child_type(syntax_tree->current_node->value)
			|| node_is_of_a_double_child_type(syntax_tree->current_node->value))
		&& !syntax_tree->current_node->primary_child)
		return (slot_into_primary_child_of_current_node(new_node,
				syntax_tree));
	else if (node_is_of_a_double_child_type(syntax_tree->current_node->value)
		&& !syntax_tree->current_node->secondary_child)
		return (slot_into_secondary_child_of_current_node(new_node,
				syntax_tree));
	else
		return (slot_into_secondary_child_of_new_sequence_node(new_node,
				syntax_tree));
}
