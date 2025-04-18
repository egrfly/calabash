/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave_quoted_section.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:02:45 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 08:04:48 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../interface/interface.h"
#include "../lex.h"
#include "../context_utils/context_utils.h"
#include "../input_utils/input_utils.h"
#include "../token_utils/token_utils.h"

bool	leave_quoted_section(
			t_input_tracker *input_tracker,
			t_tokens_with_status *tokens_with_status,
			t_multiline_options *multiline_options)
{
	t_token	*last_token;

	(void)multiline_options;
	last_token = get_last_token(tokens_with_status->tokens);
	if (input_tracker->quote_mode == ESCAPED
		|| (input_tracker->quote_mode == SINGLE_QUOTED
			&& get_current_char(input_tracker) == '\'')
		|| (input_tracker->quote_mode == DOUBLE_QUOTED
			&& get_current_char(input_tracker) == '\"'))
	{
		add_to_token_context_and_advance(input_tracker, last_token,
			&tokens_with_status->out_of_memory);
		if (tokens_with_status->out_of_memory)
			return (false);
		input_tracker->quote_mode = UNQUOTED;
		return (true);
	}
	return (false);
}
