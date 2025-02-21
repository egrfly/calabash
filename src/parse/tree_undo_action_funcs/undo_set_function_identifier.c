/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_set_function_identifier.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 00:24:41 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/19 00:25:38 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../parse.h"

void	undo_set_function_identifier(
			t_syntax_tree *syntax_tree)
{
	t_syntax_tree_node_value	*current_node_value;

	current_node_value = syntax_tree->current_node->value;
	free(current_node_value->function_identifier);
	current_node_value->function_identifier = NULL;
}
