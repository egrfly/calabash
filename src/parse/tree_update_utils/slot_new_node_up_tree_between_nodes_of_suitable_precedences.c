/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot_new_node_up_tree_between_nodes_of_suit        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:16:46 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 06:33:14 by emflynn          ###   ########.fr       */
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

static const
	int
	g_node_precedences[] = {
[SIMPLE_COMMAND] = 0,
[GROUP] = 80,
[SUBSHELL] = 80,
[WHILE_COMMAND] = 70,
[UNTIL_COMMAND] = 70,
[IF_COMMAND] = 70,
[FOR_COMMAND] = 70,
[SELECT_COMMAND] = 70,
[CASE_COMMAND] = 70,
[FUNCTION] = 10,
[PIPE] = 20,
[PIPE_BOTH] = 20,
[TIME_COMMAND] = 30,
[NEGATION] = 30,
[OR] = 40,
[AND] = 40,
[SEQUENCE] = 60,
[BACKGROUND] = 50,
[COPROCESS] = 10,
};

static bool	slot_new_node_between_current_node_and_parent(
				t_binary_tree_node *new_node,
				t_syntax_tree *syntax_tree)
{
	if (node_is_primary_child_of_parent(syntax_tree->current_node))
	{
		if (!ft_list_append(syntax_tree->undo_actions,
				undo_slot_new_node_between_current_primary_child_and_parent))
			return (false);
		syntax_tree->current_node->parent->primary_child = new_node;
	}
	else if (node_is_secondary_child_of_parent(syntax_tree->current_node))
	{
		if (!ft_list_append(syntax_tree->undo_actions,
				undo_slot_new_node_between_current_secondary_child_and_parent))
			return (false);
		syntax_tree->current_node->parent->secondary_child = new_node;
	}
	else
		return (false);
	syntax_tree->current_node->parent = new_node;
	return (true);
}

static bool	adjust_current_node_up_tree_between_nodes_of_suitable_precedences(
				t_syntax_tree_node_value_type new_node_type,
				t_syntax_tree *syntax_tree)
{
	while (syntax_tree->current_node->parent
		&& g_node_precedences[((t_syntax_tree_node_value *)
				syntax_tree->current_node->value)->type]
		< g_node_precedences[new_node_type]
		&& g_node_precedences[((t_syntax_tree_node_value *)
				syntax_tree->current_node->parent->value)->type]
		<= g_node_precedences[new_node_type])
		if (!adjust_current_node_from_child_to_parent(syntax_tree))
			return (false);
	return (true);
}

bool	slot_new_node_up_tree_between_nodes_of_suitable_precedences(
			t_syntax_tree_node_value_type new_node_type,
			t_syntax_tree *syntax_tree)
{
	t_binary_tree_node		*new_node;

	if (!adjust_current_node_up_tree_between_nodes_of_suitable_precedences(
			new_node_type, syntax_tree))
		return (false);
	new_node = create_syntax_tree_node(new_node_type);
	if (!new_node)
		return (false);
	new_node->parent = syntax_tree->current_node->parent;
	new_node->primary_child = syntax_tree->current_node;
	if (syntax_tree->current_node->parent)
	{
		if (!slot_new_node_between_current_node_and_parent(new_node,
				syntax_tree))
			return (destroy_syntax_tree_node(new_node), false);
	}
	else
	{
		if (!ft_list_append(syntax_tree->undo_actions,
				undo_set_tree_root_to_new_tree_root_parent))
			return (destroy_syntax_tree_node(new_node), false);
		syntax_tree->tree->root->parent = new_node;
		syntax_tree->tree->root = syntax_tree->tree->root->parent;
	}
	return (true);
}
