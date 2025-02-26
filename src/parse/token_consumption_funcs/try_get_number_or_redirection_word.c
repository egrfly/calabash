/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_number_or_redirection_word.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:59:07 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 14:26:20 by emflynn          ###   ########.fr       */
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
	g_number_sequence[] = {
{
	.token_consumption_func = try_get_number,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = update_command_with_new_redirection_left_number,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_redirection_word_sequence[] = {
{
	.token_consumption_func = try_get_redirection_word,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func
	= update_command_with_new_redirection_left_redirection_word,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option_sequence_with_count
	g_number_sequence_with_count = {
	.name = "number",
	.sequence = g_number_sequence,
	.count = sizeof(g_number_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_redirection_word_sequence_with_count = {
	.name = "redirection word",
	.sequence = g_redirection_word_sequence,
	.count = sizeof(g_redirection_word_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	*g_number_or_redirection_word_sequences[] = {
	&g_number_sequence_with_count,
	&g_redirection_word_sequence_with_count,
	NULL,
};

int	try_get_number_or_redirection_word(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	(void)arg;
	return (parse_recursively(current_token_node,
			syntax_tree,
			multiline_options,
			g_number_or_redirection_word_sequences));
}
