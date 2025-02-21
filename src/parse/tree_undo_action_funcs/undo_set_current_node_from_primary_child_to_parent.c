/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_set_current_node_from_primary_child_to        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 00:29:29 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/19 00:31:03 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	undo_set_current_node_from_primary_child_to_parent(
			t_syntax_tree *syntax_tree)
{
	syntax_tree->current_node = syntax_tree->current_node->primary_child;
}
