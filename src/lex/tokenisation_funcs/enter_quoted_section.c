/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enter_quoted_section.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:29:35 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/11 23:46:55 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "ft_string.h"
#include "../../interface/interface.h"
#include "../lex.h"
#include "../context_utils/context_utils.h"
#include "../input_utils/input_utils.h"
#include "../token_lifecycle/token_lifecycle.h"
#include "../token_utils/token_utils.h"

static void	set_quote_mode(t_input_tracker *input_tracker)
{
	char	quote_char;

	quote_char = get_current_char(input_tracker);
	if (quote_char == '\\')
		input_tracker->quote_mode = ESCAPED;
	else if (quote_char == '\"')
		input_tracker->quote_mode = DOUBLE_QUOTED;
	else if (quote_char == '\'')
		input_tracker->quote_mode = SINGLE_QUOTED;
}

static bool	reached_backslash_newline_sequence(t_input_tracker *input_tracker)
{
	return (get_current_char(input_tracker) == '\\'
		&& !get_next_char(input_tracker));
}

bool	enter_quoted_section(
			t_input_tracker *input_tracker,
			t_list *tokens,
			t_multiline_options *multiline_options,
			bool *has_error)
{
	t_token	*last_token;

	(void)multiline_options;
	last_token = get_last_token(tokens);
	if (input_tracker->quote_mode == UNQUOTED
		&& ft_strchr("\\\"\'", get_current_char(input_tracker)))
	{
		if (last_token && last_token->type != WORD)
			delimit_last_token_if_exists(input_tracker, last_token, has_error);
		if (!(last_token && !last_token->is_delimited)
			&& !reached_backslash_newline_sequence(input_tracker))
		{
			start_token(input_tracker, tokens, create_word_token, has_error);
			if (*has_error)
				return (false);
			last_token = tokens->last->value;
		}
		if (last_token && !last_token->is_delimited)
			add_to_token_context_if_space_available(input_tracker, last_token);
		set_quote_mode(input_tracker);
		input_tracker->index_in_line++;
		return (true);
	}
	return (false);
}
