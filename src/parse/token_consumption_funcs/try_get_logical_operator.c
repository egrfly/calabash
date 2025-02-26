/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_logical_operator.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:25:02 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 14:11:03 by emflynn          ###   ########.fr       */
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
	g_or_operator_sequence[] = {
{
	.token_consumption_func = try_get_operator,
	.token_consumption_func_arg = (void *)BAR_BAR,
	.tree_update_func = update_with_new_mid_or_post_command_node,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_and_operator_sequence[] = {
{
	.token_consumption_func = try_get_operator,
	.token_consumption_func_arg = (void *)AMPERSAND_AMPERSAND,
	.tree_update_func = update_with_new_mid_or_post_command_node,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option_sequence_with_count
	g_or_operator_sequence_with_count = {
	.name = "or operator",
	.sequence = g_or_operator_sequence,
	.count = sizeof(g_or_operator_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_and_operator_sequence_with_count = {
	.name = "and operator",
	.sequence = g_and_operator_sequence,
	.count = sizeof(g_and_operator_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	*g_logical_operator_sequences[] = {
	&g_or_operator_sequence_with_count,
	&g_and_operator_sequence_with_count,
	NULL,
};

int	try_get_logical_operator(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	(void)arg;
	return (parse_recursively(current_token_node,
			syntax_tree,
			multiline_options,
			g_logical_operator_sequences));
}
