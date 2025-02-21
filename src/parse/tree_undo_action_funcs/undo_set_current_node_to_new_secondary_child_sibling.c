/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_set_current_node_to_new_secondary_chil        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 00:50:54 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/20 22:06:11 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../parse.h"
#include "../tree_node_lifecycle/tree_node_lifecycle.h"

void	undo_set_current_node_to_new_secondary_child_sibling(
			t_syntax_tree *syntax_tree)
{
	syntax_tree->current_node
		= syntax_tree->current_node->parent->primary_child;
	destroy_syntax_tree_node(
		syntax_tree->current_node->parent->secondary_child);
	syntax_tree->current_node->parent->secondary_child = NULL;
}
