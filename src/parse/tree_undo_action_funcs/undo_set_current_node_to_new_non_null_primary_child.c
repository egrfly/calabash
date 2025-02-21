/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_set_current_node_primary_child_to_new_        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 00:40:30 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/19 01:22:21 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../parse.h"
#include "../tree_node_lifecycle/tree_node_lifecycle.h"

void	undo_set_current_node_to_new_non_null_primary_child(
			t_syntax_tree *syntax_tree)
{
	syntax_tree->current_node = syntax_tree->current_node->parent;
	destroy_syntax_tree_node(syntax_tree->current_node->primary_child);
	syntax_tree->current_node->primary_child = NULL;
}
