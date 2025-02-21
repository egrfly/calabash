/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_is_secondary_child_of_parent.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 01:32:24 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/20 02:44:22 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../parse.h"

bool	node_is_secondary_child_of_parent(
			t_binary_tree_node *node)
{
	return (node->parent && node == node->parent->secondary_child);
}
