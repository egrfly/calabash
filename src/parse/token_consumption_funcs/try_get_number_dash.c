/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_number_dash.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 23:52:25 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 06:17:48 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_ctype.h"
#include "ft_list.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "../../interface/interface.h"
#include "../../lex/lex.h"
#include "../parse.h"

int	try_get_number_dash(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	t_token	*current_token;
	size_t	word_len;
	int		number;

	(void)arg;
	(void)syntax_tree;
	(void)multiline_options;
	current_token = (*current_token_node)->value;
	if (current_token->type == TYPE_WORD)
	{
		word_len = ft_strlen(current_token->content.word);
		if (ft_strnall(current_token->content.word, ft_isdigit, word_len - 1)
			&& ft_strntoi(current_token->content.word, &number, word_len - 1)
			&& current_token->content.word[word_len - 1] == '-')
		{
			current_token->has_been_consumed_at_some_point = true;
			*current_token_node = (*current_token_node)->next;
			return (1);
		}
	}
	return (0);
}
