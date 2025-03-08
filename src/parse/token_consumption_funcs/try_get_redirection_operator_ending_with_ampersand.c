/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_redirection_operator_ending_with_am        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:25:02 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/07 05:08:08 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "../../interface/interface.h"
#include "../../lex/lex.h"
#include "../parse.h"
#include "../parsing_utils/parsing_utils.h"
#include "../tree_update_funcs/tree_update_funcs.h"
#include "./token_consumption_funcs.h"

static const
	t_parsing_option
	g_duplicate_input_operator_sequence[] = {
{
	.token_consumption_func = try_get_operator,
	.token_consumption_func_arg = (void *)LESS_AMPERSAND,
	.tree_update_func = update_command_with_new_redirection_operator,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_duplicate_output_operator_sequence[] = {
{
	.token_consumption_func = try_get_operator,
	.token_consumption_func_arg = (void *)GREATER_AMPERSAND,
	.tree_update_func = update_command_with_new_redirection_operator,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option_sequence_with_count
	g_duplicate_input_operator_sequence_with_count = {
	.name = "duplicate input operator",
	.sequence = g_duplicate_input_operator_sequence,
	.count = sizeof(g_duplicate_input_operator_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_duplicate_output_operator_sequence_with_count = {
	.name = "duplicate output operator",
	.sequence = g_duplicate_output_operator_sequence,
	.count = sizeof(g_duplicate_output_operator_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	*g_redirection_symbol_ending_with_ampersand_sequences[] = {
	&g_duplicate_input_operator_sequence_with_count,
	&g_duplicate_output_operator_sequence_with_count,
	NULL,
};

int	try_get_redirection_operator_ending_with_ampersand(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	(void)arg;
	return (parse_recursively(current_token_node,
			syntax_tree,
			multiline_options,
			g_redirection_symbol_ending_with_ampersand_sequences));
}
