/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_reserved_word.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:03:57 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 09:11:38 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "ft_string.h"
#include "../../interface/interface.h"
#include "../parse.h"

int	try_get_reserved_word(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	char	*reserved_word;
	t_token	*current_token;

	(void)syntax_tree;
	(void)multiline_options;
	reserved_word = arg;
	current_token = (*current_token_node)->value;
	if (current_token->type == WORD
		&& !ft_strcmp(current_token->content.word, reserved_word))
	{
		current_token->has_been_consumed_at_some_point = true;
		*current_token_node = (*current_token_node)->next;
		return (1);
	}
	return (0);
}
