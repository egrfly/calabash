/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_single_line_whitespace.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 04:31:29 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 06:37:16 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../../interface/interface.h"
#include "../parse.h"

int	try_get_single_line_whitespace(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	int		tokens_consumed_count;
	t_token	*current_token;

	(void)arg;
	(void)syntax_tree;
	(void)multiline_options;
	tokens_consumed_count = 0;
	current_token = (*current_token_node)->value;
	while (current_token->type == WHITESPACE)
	{
		current_token->has_been_consumed_at_some_point = true;
		*current_token_node = (*current_token_node)->next;
		current_token = (*current_token_node)->value;
		tokens_consumed_count++;
	}
	return (tokens_consumed_count);
}
