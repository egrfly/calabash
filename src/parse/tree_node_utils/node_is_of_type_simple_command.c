/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_is_of_type_simple_command.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 02:57:17 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/20 17:22:42 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../parse.h"

bool	node_is_of_type_simple_command(
			t_syntax_tree_node_value *node_value)
{
	return (node_value->type == SIMPLE_COMMAND);
}
