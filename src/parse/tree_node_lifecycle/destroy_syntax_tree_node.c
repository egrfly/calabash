/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_syntax_tree_node.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:09:18 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 06:35:35 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_binary_tree.h"
#include "ft_list.h"
#include "../parse.h"
#include "../redirection_lifecycle/redirection_lifecycle.h"

void	destroy_syntax_tree_node(
			t_binary_tree_node *node)
{
	t_syntax_tree_node_value	*node_value;

	if (node)
	{
		node_value = node->value;
		if (node_value)
		{
			if (node_value->assignments)
				ft_list_destroy(node_value->assignments, free);
			if (node_value->arguments)
				ft_list_destroy(node_value->arguments, free);
			if (node_value->redirections)
				ft_list_destroy(node_value->redirections,
					(t_action_func)destroy_redirection);
			if (node_value->coprocess_custom_identifier)
				free(node_value->coprocess_custom_identifier);
			if (node_value->function_identifier)
				free(node_value->function_identifier);
			free(node_value);
		}
		free(node);
	}
}
