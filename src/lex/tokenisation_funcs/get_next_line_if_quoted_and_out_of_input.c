/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_if_quoted_and_out_of_input.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 00:50:47 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/10 17:23:19 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "ft_list.h"
#include "../lex.h"
#include "../content_utils/content_utils.h"
#include "../context_utils/context_utils.h"
#include "../input_utils/input_utils.h"
#include "../token_utils/token_utils.h"

static void	ensure_quote_mode_is_not_escaped(
				t_input_tracker *input_tracker)
{
	if (input_tracker->quote_mode == ESCAPED)
		input_tracker->quote_mode = UNQUOTED;
	if (input_tracker->quote_mode == DOUBLE_QUOTED_AND_ESCAPED)
		input_tracker->quote_mode = DOUBLE_QUOTED;
}

static void	update_input_tracker_with_next_line_of_input_if_available(
				t_input_tracker *input_tracker,
				t_multiline_options *multiline_options)
{
	char	*next_line_of_input;

	next_line_of_input
		= multiline_options->get_next_line(
			multiline_options->get_next_line_arg);
	if (next_line_of_input)
	{
		free(input_tracker->input);
		input_tracker->input = next_line_of_input;
		input_tracker->line_index++;
		input_tracker->index_in_line = 0;
	}
	else
		input_tracker->is_out_of_lines = true;
}

bool	get_next_line_if_quoted_and_out_of_input(
			t_input_tracker *input_tracker,
			t_list *tokens,
			t_multiline_options *multiline_options,
			bool *has_error)
{
	t_token	*last_token;

	if (input_tracker->quote_mode != UNQUOTED
		&& !get_current_char(input_tracker))
	{
		ensure_quote_mode_is_not_escaped(input_tracker);
		last_token = get_last_token(tokens);
		if (last_token)
		{
			extend_word_token_content(input_tracker, last_token, has_error);
			if (*has_error)
				return (false);
		}
		update_input_tracker_with_next_line_of_input_if_available(
			input_tracker, multiline_options);
		return (true);
	}
	return (false);
}
