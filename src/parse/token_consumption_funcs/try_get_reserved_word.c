/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_reserved_word.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:03:57 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/09 01:20:36 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "ft_string.h"
#include "../../interface/interface.h"
#include "../../lex/lex.h"
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
	if (!*current_token_node)
		return (0);
	current_token = (*current_token_node)->value;
	if (current_token->type == TYPE_WORD
		&& !ft_strcmp(current_token->content.word, reserved_word))
	{
		current_token->has_been_consumed_at_some_point = true;
		*current_token_node = (*current_token_node)->next;
		return (1);
	}
	return (0);
}
