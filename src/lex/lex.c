/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:03:24 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 23:05:10 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "ft_stdlib.h"
#include "../interface/interface.h"
#include "./lex.h"
#include "./token_lifecycle/token_lifecycle.h"
#include "./tokenisation_funcs/tokenisation_funcs.h"
#include "./tokens_with_status_lifecycle/tokens_with_status_lifecycle.h"
#include "../execute/signals/signals.h"

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
			|| tokens_with_status->contains_unsupported_features)
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
			|| tokens_with_status->contains_unsupported_features)
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
				tokens_with_status->input_terminated_prematurely = true;
			return (tokens_with_status);
		}
		if (tokens_with_status->out_of_memory
			|| tokens_with_status->contains_unsupported_features
			|| !any_non_terminating_tokenisation_func_called_without_error(
				input_tracker, multiline_options,
				tokens_with_status)
			|| g_signal == SIGINT)
			break ;
	}
	return (tokens_with_status);
}

t_tokens_with_status	*lex(
							char *input,
							t_multiline_options *multiline_options,
							int start_line_index)
{
	t_input_tracker			*input_tracker;
	t_tokens_with_status	*tokens_with_status;

	input_tracker = ft_calloc(1, sizeof(t_input_tracker));
	if (!input_tracker)
		return (NULL);
	input_tracker->input = input;
	input_tracker->line_index = start_line_index;
	tokens_with_status
		= get_tokens_with_status(input_tracker,
			multiline_options);
	free(input_tracker->input);
	free(input_tracker);
	return (tokens_with_status);
}
