/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expanded_section.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:57:41 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/25 22:23:02 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_ctype.h"
#include "ft_list.h"
#include "ft_string.h"
#include "../../interface/interface.h"
#include "../lex.h"
#include "../context_utils/context_utils.h"
#include "../input_utils/input_utils.h"
#include "../token_lifecycle/token_lifecycle.h"
#include "../token_utils/token_utils.h"

static const
	char
	*g_expansion_opening_symbols[] = {
[ARITHMETIC_EXPANSION] = "$((",
[COMMAND_SUBSTITUTION_WITH_DOLLAR_PARENTHESES] = "$(",
[VARIABLE_EXPANSION_WITH_BRACES] = "${",
[VARIABLE_EXPANSION_WITHOUT_BRACES] = "$",
[PROCESS_SUBSTITUTION_WITH_LESS] = "<(",
[PROCESS_SUBSTITUTION_WITH_GREATER] = ">(",
[COMMAND_SUBSTITUTION_WITH_BACKTICKS] = "`",
};

static const
	char
	*g_expansion_closing_symbols[] = {
[ARITHMETIC_EXPANSION] = "))",
[COMMAND_SUBSTITUTION_WITH_DOLLAR_PARENTHESES] = ")",
[VARIABLE_EXPANSION_WITH_BRACES] = "}",
[VARIABLE_EXPANSION_WITHOUT_BRACES] = NULL,
[PROCESS_SUBSTITUTION_WITH_LESS] = ")",
[PROCESS_SUBSTITUTION_WITH_GREATER] = ")",
[COMMAND_SUBSTITUTION_WITH_BACKTICKS] = "`",
};

static int	get_expansion_mode(
				t_input_tracker *input_tracker)
{
	size_t	i;

	i = 1;
	while (i < sizeof(g_expansion_opening_symbols)
		/ sizeof(char *))
	{
		if (ft_strstarts(
				get_current_char_pointer(input_tracker),
				g_expansion_opening_symbols[i]))
			return (i);
		i++;
	}
	return (0);
}

static void	handle_variable_expansion_without_braces(
				t_input_tracker *input_tracker,
				t_token *last_token)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(g_expansion_opening_symbols[
				VARIABLE_EXPANSION_WITHOUT_BRACES]))
	{
		add_to_token_context_and_advance(input_tracker, last_token);
		i++;
	}
	if (get_current_char(input_tracker)
		&& ft_strchr("@*#?-$!0123456789", get_current_char(input_tracker)))
		add_to_token_context_and_advance(input_tracker, last_token);
	else if (ft_isalpha(get_current_char(input_tracker))
		|| get_current_char(input_tracker) == '_')
	{
		add_to_token_context_and_advance(input_tracker, last_token);
		while (ft_isalnum(get_current_char(input_tracker))
			|| get_current_char(input_tracker) == '_')
			add_to_token_context_and_advance(input_tracker, last_token);
	}
}

static void	handle_variable_expansion_with_braces(
				t_input_tracker *input_tracker,
				t_token *last_token)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(g_expansion_opening_symbols[
				VARIABLE_EXPANSION_WITH_BRACES]))
	{
		add_to_token_context_and_advance(input_tracker, last_token);
		i++;
	}
	while (get_current_char(input_tracker)
		&& !ft_strstarts(
			get_current_char_pointer(input_tracker),
			g_expansion_closing_symbols[
				VARIABLE_EXPANSION_WITH_BRACES]))
		add_to_token_context_and_advance(input_tracker, last_token);
}

static void	handle_unsupported_expansion_mode(
				t_expansion_mode expansion_mode,
				t_input_tracker *input_tracker,
				t_token *last_token,
				t_tokens_with_status *tokens_with_status)
{
	size_t	i;

	delimit_last_token_if_exists(input_tracker, last_token,
		&tokens_with_status->out_of_memory);
	start_token(input_tracker, tokens_with_status, create_word_token);
	if (tokens_with_status->out_of_memory)
		return ;
	last_token = get_last_token(tokens_with_status->tokens);
	i = 0;
	while (i < ft_strlen(g_expansion_opening_symbols[expansion_mode]))
	{
		add_to_token_context_and_advance(input_tracker, last_token);
		i++;
	}
	last_token->is_supported = false;
	tokens_with_status->contains_unsupported_features = true;
	delimit_last_token_if_exists(input_tracker, last_token,
		&tokens_with_status->out_of_memory);
}

bool	handle_expanded_section(
			t_input_tracker *input_tracker,
			t_tokens_with_status *tokens_with_status,
			t_multiline_options *multiline_options)
{
	t_token				*last_token;
	t_expansion_mode	expansion_mode;

	(void)multiline_options;
	last_token = get_last_token(tokens_with_status->tokens);
	expansion_mode = get_expansion_mode(input_tracker);
	if (expansion_mode && (input_tracker->quote_mode == UNQUOTED
			|| input_tracker->quote_mode == DOUBLE_QUOTED))
	{
		if (last_token && last_token->type != TYPE_WORD)
			delimit_last_token_if_exists(input_tracker, last_token,
				&tokens_with_status->out_of_memory);
		if (!advance_to_new_word_token_if_necessary(input_tracker,
				&last_token, tokens_with_status))
			return (false);
		if (expansion_mode == VARIABLE_EXPANSION_WITHOUT_BRACES)
			return (handle_variable_expansion_without_braces(
					input_tracker, last_token), true);
		if (expansion_mode == VARIABLE_EXPANSION_WITH_BRACES)
			return (handle_variable_expansion_with_braces(
					input_tracker, last_token), true);
		return (handle_unsupported_expansion_mode(expansion_mode,
				input_tracker, last_token, tokens_with_status), false);
	}
	return (false);
}
