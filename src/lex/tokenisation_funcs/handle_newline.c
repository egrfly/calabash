/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_newline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 05:05:15 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 06:14:08 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../interface/interface.h"
#include "../lex.h"
#include "../input_utils/input_utils.h"
#include "../token_lifecycle/token_lifecycle.h"
#include "../token_utils/token_utils.h"

static bool	is_valid_newline_start_opportunity(
				t_input_tracker *input_tracker)
{
	return (input_tracker->quote_mode == UNQUOTED
		&& get_current_char(input_tracker) == '\n');
}

bool	handle_newline(
			t_input_tracker *input_tracker,
			t_tokens_with_status *tokens_with_status,
			t_multiline_options *multiline_options)
{
	(void)multiline_options;
	if (is_valid_newline_start_opportunity(input_tracker)
		&& start_token(input_tracker,
			tokens_with_status,
			create_newline_token))
	{
		input_tracker->current_input_line
			= get_next_char_pointer(input_tracker);
		input_tracker->line_index++;
		input_tracker->index_in_line = 0;
		return (true);
	}
	return (false);
}
