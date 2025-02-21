/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo_create_argument.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 00:19:42 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/19 00:22:57 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "../parse.h"

void	undo_create_argument(
			t_syntax_tree *syntax_tree)
{
	t_syntax_tree_node_value	*current_node_value;
	char						*last_argument;

	current_node_value = syntax_tree->current_node->value;
	last_argument = ft_list_pop(current_node_value->arguments);
	free(last_argument);
}
