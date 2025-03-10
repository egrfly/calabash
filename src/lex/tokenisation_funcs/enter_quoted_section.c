/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enter_quoted_section.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:29:35 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 08:50:52 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_string.h"
#include "../../interface/interface.h"
#include "../lex.h"
#include "../context_utils/context_utils.h"
#include "../input_utils/input_utils.h"
#include "../token_lifecycle/token_lifecycle.h"
#include "../token_utils/token_utils.h"

static void	set_quote_mode(
				t_input_tracker *input_tracker)
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

static void	update_last_opening_quote_details(
				t_input_tracker *input_tracker,
				t_token *token)
{
	if (token->content.word)
		token->last_opening_quote_line_start_index_in_word_content
			= ft_strlen(token->content.word);
	if (token->start_line_index != input_tracker->line_index)
		token->last_opening_quote_index_in_word_content_line
			= input_tracker->index_in_line;
	else
		token->last_opening_quote_index_in_word_content_line
			= input_tracker->index_in_line - token->start_index_in_start_line;
	token->last_opening_quote_line_index = input_tracker->line_index;
	token->last_opening_quote_index_in_line = input_tracker->index_in_line;
}

static bool	reached_backslash_newline_sequence(
				t_input_tracker *input_tracker)
{
	return (get_current_char(input_tracker) == '\\'
		&& (!get_next_char(input_tracker)
			|| get_next_char(input_tracker) == '\n'));
}

bool	enter_quoted_section(
			t_input_tracker *input_tracker,
			t_tokens_with_status *tokens_with_status,
			t_multiline_options *multiline_options)
{
	t_token	*last_token;

	(void)multiline_options;
	last_token = get_last_token(tokens_with_status->tokens);
	if (input_tracker->quote_mode == UNQUOTED
		&& ft_strchr("\\\"\'", get_current_char(input_tracker)))
	{
		if (last_token && last_token->type != TYPE_WORD)
			delimit_last_token_if_exists(input_tracker, last_token,
				&tokens_with_status->out_of_memory);
		if (!reached_backslash_newline_sequence(input_tracker)
			&& !advance_to_new_word_token_if_necessary(input_tracker,
				&last_token, tokens_with_status))
			return (false);
		set_quote_mode(input_tracker);
		if (input_tracker->quote_mode != ESCAPED)
			update_last_opening_quote_details(input_tracker, last_token);
		if (last_token && !last_token->is_delimited)
			add_to_token_context_and_advance(input_tracker, last_token,
				&tokens_with_status->out_of_memory);
		else
			input_tracker->index_in_line++;
		return (!tokens_with_status->out_of_memory);
	}
	return (false);
}
