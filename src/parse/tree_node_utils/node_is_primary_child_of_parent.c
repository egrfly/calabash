/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_is_primary_child_of_parent.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 01:32:24 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/19 01:34:18 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../parse.h"

bool	node_is_primary_child_of_parent(
			t_binary_tree_node *node)
{
	return (node->parent && node == node->parent->primary_child);
}
