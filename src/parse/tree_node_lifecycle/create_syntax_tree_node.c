/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_syntax_tree_node.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:01:31 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 07:05:37 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_binary_tree.h"
#include "ft_list.h"
#include "ft_stdlib.h"
#include "../parse.h"
#include "../tree_node_utils/tree_node_utils.h"
#include "./tree_node_lifecycle.h"

static bool	init_simple_command_specific_elements(
				t_syntax_tree_node_value *node_value)
{
	node_value->assignments = ft_list_init();
	node_value->arguments = ft_list_init();
	return (node_value->assignments && node_value->arguments);
}

static bool	init_simple_or_shell_command_specific_elements(
				t_syntax_tree_node_value *node_value)
{
	node_value->redirections = ft_list_init();
	return (node_value->redirections);
}

t_binary_tree_node	*create_syntax_tree_node(
						t_syntax_tree_node_value_type type)
{
	t_binary_tree_node			*node;
	t_syntax_tree_node_value	*node_value;

	node_value = ft_calloc(sizeof(t_syntax_tree_node_value), 1);
	if (!node_value)
		return (NULL);
	node = ft_binary_tree_newnode(node_value);
	if (!node)
		return (free(node_value), NULL);
	node_value->type = type;
	if (type == SIMPLE_COMMAND
		&& !init_simple_command_specific_elements(node_value))
		return (destroy_syntax_tree_node(node), NULL);
	if (node_is_of_type_simple_or_shell_command(node_value)
		&& !init_simple_or_shell_command_specific_elements(node_value))
		return (destroy_syntax_tree_node(node), NULL);
	return (node);
}
