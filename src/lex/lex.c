/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:03:24 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/29 14:12:50 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "ft_list.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "../interface/interface.h"
#include "../interface/line_getters/line_getters.h"
#include "../execute/signals/signals.h"
#include "./lex.h"
#include "./token_lifecycle/token_lifecycle.h"
#include "./tokenisation_funcs/tokenisation_funcs.h"
#include "./tokens_with_status_lifecycle/tokens_with_status_lifecycle.h"

static const
	t_tokenisation_func
	g_terminating_tokenisation_funcs[] = {
	delimit_token_if_at_end_of_input,
};

static const
	t_tokenisation_func
	g_non_terminating_tokenisation_funcs[] = {
	get_next_line_if_quoted_and_out_of_input,
	handle_expanded_section,
	continue_operator,
	delimit_operator,
	leave_quoted_section,
	handle_double_quoted_and_escaped_char,
	handle_backslash_in_double_quotes,
	enter_quoted_section,
	start_operator,
	handle_newline,
	continue_whitespace,
	start_whitespace,
	continue_word,
	handle_comment,
	start_word,
};

static bool	any_terminating_tokenisation_func_called_without_error(
				t_input_tracker *input_tracker,
				t_multiline_options *multiline_options,
				t_tokens_with_status *tokens_with_status)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_terminating_tokenisation_funcs)
		/ sizeof(t_tokenisation_func))
	{
		if ((*g_terminating_tokenisation_funcs[i])(
			input_tracker, tokens_with_status, multiline_options))
			return (true);
		if (tokens_with_status->out_of_memory
			|| tokens_with_status->contains_unsupported_features
			|| tokens_with_status->expanded_section_not_closed)
			return (false);
		i++;
	}
	return (false);
}

static bool	any_non_terminating_tokenisation_func_called_without_error(
				t_input_tracker *input_tracker,
				t_multiline_options *multiline_options,
				t_tokens_with_status *tokens_with_status)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_non_terminating_tokenisation_funcs)
		/ sizeof(t_tokenisation_func))
	{
		if ((*g_non_terminating_tokenisation_funcs[i])(
			input_tracker, tokens_with_status, multiline_options))
			return (true);
		if (tokens_with_status->out_of_memory
			|| tokens_with_status->contains_unsupported_features
			|| tokens_with_status->expanded_section_not_closed)
			return (false);
		i++;
	}
	return (false);
}

static t_tokens_with_status	*get_tokens_with_status(
								t_input_tracker *input_tracker,
								t_multiline_options *multiline_options)
{
	t_tokens_with_status	*tokens_with_status;

	tokens_with_status = create_tokens_with_status();
	if (!tokens_with_status)
		return (NULL);
	while (true)
	{
		if (any_terminating_tokenisation_func_called_without_error(
				input_tracker, multiline_options,
				tokens_with_status))
		{
			if (input_tracker->quote_mode != UNQUOTED)
				tokens_with_status->quoted_section_not_closed = true;
			return (tokens_with_status);
		}
		if (g_signal == SIGINT
			|| tokens_with_status->out_of_memory
			|| tokens_with_status->contains_unsupported_features
			|| tokens_with_status->expanded_section_not_closed
			|| !any_non_terminating_tokenisation_func_called_without_error(
				input_tracker, multiline_options,
				tokens_with_status))
			break ;
	}
	return (tokens_with_status);
}

t_tokens_with_status	*lex(
							char *input,
							t_multiline_options *multiline_options,
							int start_line_index)
{
	t_input_tracker			input_tracker;
	t_tokens_with_status	*tokens_with_status;

	ft_bzero(&input_tracker, sizeof(t_input_tracker));
	input_tracker.original_input = input;
	input_tracker.current_input_line = input;
	input_tracker.line_index = start_line_index;
	tokens_with_status
		= get_tokens_with_status(&input_tracker,
			multiline_options);
	if (multiline_options->get_next_line != noninteractive_get_null_line)
		free(input_tracker.original_input);
	return (tokens_with_status);
}
