/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_update_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:13:23 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/20 22:04:46 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_UPDATE_UTILS_H
# define TREE_UPDATE_UTILS_H

# include <stdbool.h>
# include "../parse.h"

bool	adjust_current_node_from_child_to_parent(
			t_syntax_tree *syntax_tree);
bool	adjust_current_node_to_accommodate_new_node(
			t_syntax_tree_node_value_type new_node_value_type,
			t_syntax_tree *syntax_tree);
bool	slot_new_node_up_tree_between_nodes_of_suitable_precedences(
			t_syntax_tree_node_value_type new_node_type,
			t_syntax_tree *syntax_tree);

#endif
