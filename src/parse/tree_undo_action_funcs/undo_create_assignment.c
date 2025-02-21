/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_create_assignment.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 00:17:30 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/19 00:24:07 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "../parse.h"

void	undo_create_assignment(
			t_syntax_tree *syntax_tree)
{
	t_syntax_tree_node_value	*current_node_value;
	char						*last_assignment;

	current_node_value = syntax_tree->current_node->value;
	last_assignment = ft_list_pop(current_node_value->assignments);
	free(last_assignment);
}
