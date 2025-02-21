/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_set_current_node_secondary_child_to_ne        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 00:47:03 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/19 01:23:14 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../parse.h"
#include "../tree_node_lifecycle/tree_node_lifecycle.h"

void	undo_set_current_node_to_new_non_null_secondary_child(
			t_syntax_tree *syntax_tree)
{
	syntax_tree->current_node = syntax_tree->current_node->parent;
	destroy_syntax_tree_node(syntax_tree->current_node->secondary_child);
	syntax_tree->current_node->secondary_child = NULL;
}
