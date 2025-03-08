/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_dash_or_number_dash_or_number_or_wo        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:59:07 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 06:19:22 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "../../interface/interface.h"
#include "../parse.h"
#include "../parsing_utils/parsing_utils.h"
#include "../tree_update_funcs/tree_update_funcs.h"
#include "./token_consumption_funcs.h"

static const
	t_parsing_option
	g_dash_sequence[] = {
{
	.token_consumption_func = try_get_reserved_word,
	.token_consumption_func_arg = "-",
	.tree_update_func = update_command_with_new_redirection_right_dash,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_number_dash_sequence[] = {
{
	.token_consumption_func = try_get_number_dash,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = update_command_with_new_redirection_right_number_dash,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_number_sequence[] = {
{
	.token_consumption_func = try_get_number,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = update_command_with_new_redirection_right_number,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_word_sequence[] = {
{
	.token_consumption_func = try_get_word,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = update_command_with_new_redirection_right_word,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option_sequence_with_count
	g_dash_sequence_with_count = {
	.name = "dash sequence",
	.sequence = g_dash_sequence,
	.count = sizeof(g_dash_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_number_dash_sequence_with_count = {
	.name = "number dash sequence",
	.sequence = g_number_dash_sequence,
	.count = sizeof(g_number_dash_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_number_sequence_with_count = {
	.name = "number sequence",
	.sequence = g_number_sequence,
	.count = sizeof(g_number_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_word_sequence_with_count = {
	.name = "word sequence",
	.sequence = g_word_sequence,
	.count = sizeof(g_word_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	*g_dash_or_number_dash_or_number_or_word_sequences[] = {
	&g_dash_sequence_with_count,
	&g_number_dash_sequence_with_count,
	&g_number_sequence_with_count,
	&g_word_sequence_with_count,
	NULL,
};

int	try_get_dash_or_number_dash_or_number_or_word(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	(void)arg;
	return (parse_recursively(current_token_node,
			syntax_tree,
			multiline_options,
			g_dash_or_number_dash_or_number_or_word_sequences));
}
