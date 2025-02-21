/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_multiline_whitespace.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 00:49:50 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 08:34:26 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../../interface/interface.h"
#include "../../lex/lex.h"
#include "../parse.h"
#include "../token_utils/token_utils.h"

static void	consume_available_multiline_whitespace_tokens(
				int *tokens_consumed_count,
				int *newline_tokens_consumed_count,
				t_list_node **current_token_node)
{
	while (token_is_of_type((*current_token_node)->value, NEWLINE)
		|| token_is_of_type((*current_token_node)->value, WHITESPACE))
	{
		consume_token((*current_token_node)->value);
		(*tokens_consumed_count)++;
		if (token_is_of_type((*current_token_node)->value, NEWLINE))
			(*newline_tokens_consumed_count)++;
		*current_token_node = (*current_token_node)->next;
	}
}

static bool	prompt_further_while_at_end_of_input(
		t_multiline_options *multiline_options,
		int *tokens_consumed_count,
		int *newline_tokens_consumed_count,
		t_list_node **current_token_node)
{
	char					*next_line;
	t_tokens_with_status	*next_line_tokens;
	bool					input_terminated_prematurely;

	input_terminated_prematurely = false;
	while (token_is_of_type((*current_token_node)->value, END_OF_INPUT)
		&& !input_terminated_prematurely)
	{
		next_line = multiline_options->get_next_line(
				multiline_options->get_next_line_arg);
		if (!next_line)
			break ;
		next_line_tokens = lex(next_line, multiline_options,
				get_post_token_line_index((*current_token_node)->value));
		if (next_line_tokens->input_terminated_prematurely)
			input_terminated_prematurely = true;
		set_token_type((*current_token_node)->value, NEWLINE);
		(*current_token_node)->next = next_line_tokens->tokens->first;
		next_line_tokens->tokens->first->prev = *current_token_node;
		consume_available_multiline_whitespace_tokens(tokens_consumed_count,
			newline_tokens_consumed_count,
			current_token_node);
	}
	return (!input_terminated_prematurely);
}

int	try_get_multiline_whitespace(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	bool					should_prompt_further_in_interactive_mode;
	int						tokens_consumed_count;
	int						newline_tokens_consumed_count;

	(void)syntax_tree;
	should_prompt_further_in_interactive_mode = (bool)arg;
	tokens_consumed_count = 0;
	newline_tokens_consumed_count = 0;
	consume_available_multiline_whitespace_tokens(&tokens_consumed_count,
		&newline_tokens_consumed_count,
		current_token_node);
	if (((should_prompt_further_in_interactive_mode
				|| !multiline_options->input_mode_is_interactive)
			&& !prompt_further_while_at_end_of_input(multiline_options,
				&tokens_consumed_count, &newline_tokens_consumed_count,
				current_token_node))
		|| !newline_tokens_consumed_count)
		return (0);
	return (tokens_consumed_count);
}
