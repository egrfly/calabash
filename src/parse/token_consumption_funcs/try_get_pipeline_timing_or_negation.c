/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_pipeline_timing_or_negation.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:13:59 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 14:33:49 by emflynn          ###   ########.fr       */
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
	g_time_command_sequence[] = {
{
	.token_consumption_func = try_get_time_command,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_negation_sequence[] = {
{
	.token_consumption_func = try_get_reserved_word,
	.token_consumption_func_arg = "!",
	.tree_update_func = update_with_new_pre_command_node,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option_sequence_with_count
	g_time_command_sequence_with_count = {
	.name = "time command",
	.sequence = g_time_command_sequence,
	.count = sizeof(g_time_command_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_negation_sequence_with_count = {
	.name = "negation",
	.sequence = g_negation_sequence,
	.count = sizeof(g_negation_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	*g_pipeline_timing_or_negation_sequences[] = {
	&g_time_command_sequence_with_count,
	&g_negation_sequence_with_count,
	NULL,
};

int	try_get_pipeline_timing_or_negation(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	(void)arg;
	return (parse_recursively(current_token_node,
			syntax_tree,
			multiline_options,
			g_pipeline_timing_or_negation_sequences));
}
