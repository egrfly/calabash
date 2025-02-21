/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_set_coprocess_custom_identifier.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 00:27:16 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/19 00:27:46 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../parse.h"

void	undo_set_coprocess_custom_identifier(
			t_syntax_tree *syntax_tree)
{
	t_syntax_tree_node_value	*current_node_value;

	current_node_value = syntax_tree->current_node->value;
	free(current_node_value->coprocess_custom_identifier);
	current_node_value->coprocess_custom_identifier = NULL;
}
