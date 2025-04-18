/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_multiline_whitespace.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 00:49:50 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/29 13:53:15 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_list.h"
#include "ft_stdio.h"
#include "../../execute/signals/signals.h"
#include "../../interface/interface.h"
#include "../../lex/lex.h"
#include "../parse.h"
#include "../token_utils/token_utils.h"
#include "../tree_utils/tree_utils.h"
#include "./token_consumption_funcs.h"

static void	consume_available_multiline_whitespace_tokens(
				t_list_node **current_token_node,
				t_tokens_consumed_counts *whitespace_tokens_consumed_counts)
{
	while (*current_token_node
		&& (token_is_of_type((*current_token_node)->value, TYPE_NEWLINE)
			|| token_is_of_type((*current_token_node)->value, TYPE_WHITESPACE)))
	{
		consume_token((*current_token_node)->value);
		whitespace_tokens_consumed_counts->total++;
		if (token_is_of_type((*current_token_node)->value, TYPE_NEWLINE))
			whitespace_tokens_consumed_counts->newlines++;
		*current_token_node = (*current_token_node)->next;
	}
}

static void	propagate_lexing_errors(
				t_tokens_with_status *next_line_tokens,
				t_syntax_tree *syntax_tree)
{
	if (!next_line_tokens)
	{
		syntax_tree->out_of_memory = true;
		return ;
	}
	if (next_line_tokens->out_of_memory)
		syntax_tree->out_of_memory = true;
	if (next_line_tokens->contains_unsupported_features)
		syntax_tree->contains_unsupported_features = true;
	if (next_line_tokens->quoted_section_not_closed)
		syntax_tree->quoted_section_not_closed = true;
	if (next_line_tokens->expanded_section_not_closed)
		syntax_tree->expanded_section_not_closed = true;
}

static bool	prompt_more_while_at_end_of_input(
				t_list_node **current_token_node,
				t_syntax_tree *syntax_tree,
				t_multiline_options *multiline_options,
				t_tokens_consumed_counts *whitespace_tokens_consumed_counts)
{
	char					*next_line;
	t_tokens_with_status	*next_line_tokens;

	while (*current_token_node
		&& token_is_of_type((*current_token_node)->value, TYPE_END_OF_INPUT)
		&& !tree_has_errors(syntax_tree))
	{
		next_line = multiline_options->get_next_line(
				multiline_options->get_next_line_arg);
		if (g_signal == SIGINT || !next_line)
		{
			free(next_line);
			break ;
		}
		next_line_tokens = lex(next_line, multiline_options,
				get_post_token_line_index((*current_token_node)->value));
		propagate_lexing_errors(next_line_tokens, syntax_tree);
		if (!next_line_tokens)
			return (false);
		join_tokens(*current_token_node, next_line_tokens);
		consume_available_multiline_whitespace_tokens(
			current_token_node, whitespace_tokens_consumed_counts);
	}
	return (!tree_has_errors(syntax_tree));
}

int	try_get_multiline_whitespace(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	bool						should_prompt_more_in_interactive_mode;
	t_tokens_consumed_counts	whitespace_tokens_consumed_counts;

	(void)syntax_tree;
	should_prompt_more_in_interactive_mode = (bool)arg;
	whitespace_tokens_consumed_counts.total = 0;
	whitespace_tokens_consumed_counts.newlines = 0;
	consume_available_multiline_whitespace_tokens(
		current_token_node, &whitespace_tokens_consumed_counts);
	if (((should_prompt_more_in_interactive_mode
				|| !multiline_options->input_mode_is_interactive)
			&& !prompt_more_while_at_end_of_input(current_token_node,
				syntax_tree, multiline_options,
				&whitespace_tokens_consumed_counts))
		|| whitespace_tokens_consumed_counts.newlines == 0)
		return (0);
	return (whitespace_tokens_consumed_counts.total);
}
