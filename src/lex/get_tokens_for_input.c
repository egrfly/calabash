/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens_for_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:03:24 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/08 07:11:55 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "ft_stdlib.h"
#include "./lex.h"
#include "./token_lifecycle/token_lifecycle.h"
#include "./tokenisation_funcs/tokenisation_funcs.h"

static const t_tokenisation_func	g_terminating_tokenisation_funcs[] = {
	delimit_token_if_at_end_of_input,
	delimit_token_if_at_end_of_nested_section,
	NULL,
};

static const t_tokenisation_func	g_non_terminating_tokenisation_funcs[] = {
	get_next_line_if_quoted_and_out_of_input,
	// handle_nested_parentheses,
	continue_operator,
	delimit_operator,
	leave_quoted_section,
	handle_double_quoted_and_escaped_char,
	handle_backslash_in_double_quotes,
	enter_quoted_section,
	// handle_expanded_section,
	start_operator,
	// create_newline,
	continue_whitespace,
	start_whitespace,
	continue_word,
	handle_comment,
	start_word,
	NULL,
};

static bool	any_terminating_tokenisation_func_called_without_error(
				t_input_tracker *input_tracker,
				t_multiline_options *multiline_options,
				t_list *tokens,
				bool *has_error)
{
	int	i;

	i = 0;
	while (g_terminating_tokenisation_funcs[i])
	{
		if ((*g_terminating_tokenisation_funcs[i])(
			input_tracker, tokens, multiline_options, has_error))
			return (true);
		if (*has_error)
		{
			ft_list_destroy(tokens, (t_action_func)destroy_token);
			return (false);
		}
		i++;
	}
	return (false);
}

static bool	any_non_terminating_tokenisation_func_called_without_error(
				t_input_tracker *input_tracker,
				t_multiline_options *multiline_options,
				t_list *tokens,
				bool *has_error)
{
	int	i;

	i = 0;
	while (g_non_terminating_tokenisation_funcs[i])
	{
		if ((*g_non_terminating_tokenisation_funcs[i])(
			input_tracker, tokens, multiline_options, has_error))
			return (true);
		if (*has_error)
		{
			ft_list_destroy(tokens, (t_action_func)destroy_token);
			return (false);
		}
		i++;
	}
	return (false);
}

static bool	still_quoted_or_nested(
				t_input_tracker *input_tracker)
{
	return (input_tracker->quote_mode != UNQUOTED
		|| input_tracker->nesting_mode != NOT_NESTED);
}

static t_tokens_with_status	*get_tokens_for_input_tracker(
										t_input_tracker *input_tracker,
										t_multiline_options *multiline_options)
{
	t_tokens_with_status	*tokens_with_termination_status;
	bool					has_error;

	tokens_with_termination_status
		= ft_calloc(sizeof(t_tokens_with_status), 1);
	if (!tokens_with_termination_status)
		return (NULL);
	has_error = false;
	while (true)
	{
		if (any_terminating_tokenisation_func_called_without_error(
				input_tracker, multiline_options,
				tokens_with_termination_status->tokens, &has_error))
			return (tokens_with_termination_status);
		if (has_error
			|| !any_non_terminating_tokenisation_func_called_without_error(
				input_tracker, multiline_options,
				tokens_with_termination_status->tokens, &has_error))
			break ;
	}
	if (has_error)
		return (NULL);
	if (still_quoted_or_nested(input_tracker))
		tokens_with_termination_status->terminated_prematurely = true;
	return (tokens_with_termination_status);
}

t_tokens_with_status	*get_tokens_for_input(
										char *input,
										t_multiline_options *multiline_options,
										int start_line_index)
{
	t_input_tracker	*input_tracker;

	input_tracker = ft_calloc(sizeof(t_input_tracker), 1);
	if (!input_tracker)
		return (NULL);
	input_tracker->input = input;
	input_tracker->line_index = start_line_index;
	return (get_tokens_for_input_tracker(input_tracker, multiline_options));
}
