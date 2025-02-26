/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_case_clause_terminator.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:25:02 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 13:57:08 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "../../interface/interface.h"
#include "../parse.h"
#include "../parsing_utils/parsing_utils.h"
#include "./token_consumption_funcs.h"

static const
	t_parsing_option
	g_execute_case_then_continue_operator_sequence[] = {
{
	.token_consumption_func = try_get_operator,
	.token_consumption_func_arg = (void *)SEMICOLON_SEMICOLON_AMPERSAND,
	.tree_update_func = NO_ARG,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_execute_case_then_terminate_operator_sequence[] = {
{
	.token_consumption_func = try_get_operator,
	.token_consumption_func_arg = (void *)SEMICOLON_SEMICOLON,
	.tree_update_func = NO_ARG,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_execute_case_and_next_then_terminate_operator_sequence[] = {
{
	.token_consumption_func = try_get_operator,
	.token_consumption_func_arg = (void *)SEMICOLON_AMPERSAND,
	.tree_update_func = NO_ARG,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option_sequence_with_count
	g_execute_case_then_continue_operator_sequence_with_count = {
	.name = "execute case then continue operator",
	.sequence = g_execute_case_then_continue_operator_sequence,
	.count = sizeof(g_execute_case_then_continue_operator_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_execute_case_then_terminate_operator_sequence_with_count = {
	.sequence
	= g_execute_case_then_terminate_operator_sequence,
	.count = sizeof(g_execute_case_then_terminate_operator_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_execute_case_and_next_then_terminate_operator_sequence_with_count = {
	.sequence = g_execute_case_and_next_then_terminate_operator_sequence,
	.count = sizeof(g_execute_case_and_next_then_terminate_operator_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	*g_case_clause_terminator_sequences[] = {
	&g_execute_case_then_continue_operator_sequence_with_count,
	&g_execute_case_then_terminate_operator_sequence_with_count,
	&g_execute_case_and_next_then_terminate_operator_sequence_with_count,
	NULL,
};

int	try_get_case_clause_terminator(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	(void)arg;
	return (parse_recursively(current_token_node,
			syntax_tree,
			multiline_options,
			g_case_clause_terminator_sequences));
}
