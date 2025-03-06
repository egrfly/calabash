/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_pipes_in_current_pipeline.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:04:25 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 02:05:04 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_tree.h"
#include "../../parse/parse.h"

int	count_pipes_in_current_pipeline(
		t_binary_tree_node *node)
{
	t_binary_tree_node			*current_node;
	t_syntax_tree_node_value	*current_node_value;
	int							count;

	current_node = node;
	current_node_value = current_node->value;
	count = 0;
	while (current_node_value->type == PIPE)
	{
		current_node = current_node->primary_child;
		current_node_value = current_node->value;
		count++;
	}
	return (count);
}
