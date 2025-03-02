/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_syntax_tree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:51:17 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/01 20:56:15 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_binary_tree.h"
#include "ft_list.h"
#include "ft_stdlib.h"
#include "../parse.h"
#include "./tree_lifecycle.h"

t_syntax_tree	*create_syntax_tree(void)
{
	t_syntax_tree	*syntax_tree;

	syntax_tree = ft_calloc(1, sizeof(t_syntax_tree));
	if (!syntax_tree)
		return (NULL);
	syntax_tree->tree = ft_binary_tree_init();
	syntax_tree->undo_actions = ft_list_init();
	if (!syntax_tree->tree || !syntax_tree->undo_actions)
	{
		destroy_syntax_tree(syntax_tree);
		return (NULL);
	}
	syntax_tree->current_node = syntax_tree->tree->root;
	return (syntax_tree);
}
