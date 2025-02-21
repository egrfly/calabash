/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_set_time_posix_option.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 00:26:26 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/19 00:26:54 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../parse.h"

void	undo_set_time_posix_option(
			t_syntax_tree *syntax_tree)
{
	t_syntax_tree_node_value	*current_node_value;

	current_node_value = syntax_tree->current_node->value;
	current_node_value->time_posix_option_set = false;
}
