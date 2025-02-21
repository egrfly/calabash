/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_is_of_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:03:06 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/20 20:03:50 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../parse.h"

bool	node_is_of_type(
			t_syntax_tree_node_value *node_value,
			t_syntax_tree_node_value_type type)
{
	return (node_value->type == type);
}
