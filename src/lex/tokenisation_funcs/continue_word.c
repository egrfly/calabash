/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:26:28 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 08:14:53 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../interface/interface.h"
#include "../lex.h"
#include "../token_utils/token_utils.h"

static bool	is_valid_word_continuation(
			t_input_tracker *input_tracker,
			t_token *last_token)
{
	(void)input_tracker;
	return (last_token->type == TYPE_WORD);
}

bool	continue_word(
			t_input_tracker *input_tracker,
			t_tokens_with_status *tokens_with_status,
			t_multiline_options *multiline_options)
{
	t_token	*last_token;

	(void)multiline_options;
	last_token = get_last_token(tokens_with_status->tokens);
	return (continue_token(
			input_tracker,
			last_token,
			is_valid_word_continuation,
			&tokens_with_status->out_of_memory));
}
