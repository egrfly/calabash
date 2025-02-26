/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_compound_list_connector.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:25:02 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 13:59:35 by emflynn          ###   ########.fr       */
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
	g_logical_operator_sequence[] = {
{
	.token_consumption_func = try_get_logical_operator,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_compound_list_terminator_sequence[] = {
{
	.token_consumption_func = try_get_compound_list_terminator,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option_sequence_with_count
	g_logical_operator_sequence_with_count = {
	.name = "logical operator",
	.sequence = g_logical_operator_sequence,
	.count = sizeof(g_logical_operator_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_compound_list_terminator_sequence_with_count = {
	.name = "compound list terminator",
	.sequence = g_compound_list_terminator_sequence,
	.count = sizeof(g_compound_list_terminator_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	*g_compound_list_connector_sequences[] = {
	&g_logical_operator_sequence_with_count,
	&g_compound_list_terminator_sequence_with_count,
	NULL,
};

int	try_get_compound_list_connector(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	(void)arg;
	return (parse_recursively(current_token_node,
			syntax_tree,
			multiline_options,
			g_compound_list_connector_sequences));
}
