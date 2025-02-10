/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:26:28 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/10 04:22:21 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../lex.h"
#include "../token_utils/token_utils.h"

static bool	is_valid_word_continuation(
			t_input_tracker *input_tracker,
			t_token *last_token)
{
	(void)input_tracker;
	return (last_token->type == WORD);
}

bool	continue_word(
			t_input_tracker *input_tracker,
			t_list *tokens,
			t_multiline_options *multiline_options,
			bool *has_error)
{
	t_token	*last_token;

	(void)multiline_options;
	(void)has_error;
	last_token = get_last_token(tokens);
	return (continue_token(
			input_tracker,
			last_token,
			is_valid_word_continuation));
}
