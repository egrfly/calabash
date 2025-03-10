/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_backslash_in_double_quotes.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:22:51 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 07:59:00 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../interface/interface.h"
#include "../lex.h"
#include "../context_utils/context_utils.h"
#include "../input_utils/input_utils.h"
#include "../token_utils/token_utils.h"

bool	handle_backslash_in_double_quotes(
			t_input_tracker *input_tracker,
			t_tokens_with_status *tokens_with_status,
			t_multiline_options *multiline_options)
{
	t_token	*last_token;

	(void)multiline_options;
	last_token = get_last_token(tokens_with_status->tokens);
	if (input_tracker->quote_mode == DOUBLE_QUOTED
		&& get_current_char(input_tracker) == '\\')
	{
		add_to_token_context_and_advance(input_tracker, last_token,
			&tokens_with_status->out_of_memory);
		if (tokens_with_status->out_of_memory)
			return (false);
		input_tracker->quote_mode = DOUBLE_QUOTED_AND_ESCAPED;
		return (true);
	}
	return (false);
}
