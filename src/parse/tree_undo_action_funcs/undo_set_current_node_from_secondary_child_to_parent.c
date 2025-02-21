/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_set_current_node_from_secondary_child_        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 00:31:30 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/19 00:31:47 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	undo_set_current_node_from_secondary_child_to_parent(
			t_syntax_tree *syntax_tree)
{
	syntax_tree->current_node = syntax_tree->current_node->secondary_child;
}
