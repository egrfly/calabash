/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_with_new_pre_command_node.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:56:52 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 15:01:04 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../parse.h"
#include "../tree_node_utils/tree_node_utils.h"
#include "../tree_update_utils/tree_update_utils.h"

bool	update_with_new_pre_command_node(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node)
{
	t_syntax_tree_node_value_type	new_node_type;

	new_node_type = get_node_type_from_token(current_token_node->value);
	return (adjust_current_node_to_accommodate_new_node(new_node_type,
			syntax_tree));
}
