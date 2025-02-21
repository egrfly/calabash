/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_set_tree_root_to_new_tree_root_parent.        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 01:01:07 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/20 21:30:13 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../parse.h"
#include "../tree_node_lifecycle/tree_node_lifecycle.h"

void	undo_set_tree_root_to_new_tree_root_parent(
			t_syntax_tree *syntax_tree)
{
	syntax_tree->tree->root = syntax_tree->tree->root->primary_child;
	destroy_syntax_tree_node(syntax_tree->tree->root->parent);
	syntax_tree->tree->root->parent = NULL;
}
