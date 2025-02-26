/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_optionally_timed_or_negated_pipelin        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 00:25:50 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 14:29:23 by emflynn          ###   ########.fr       */
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
	g_pipeline_sequence[] = {
{
	.token_consumption_func = try_get_optionally_timed_or_negated_pipeline,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_list_separator_sequence[] = {
{
	.token_consumption_func = try_get_list_separator,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option_sequence_with_count
	g_pipeline_sequence_with_count = {
	.name = "pipeline",
	.sequence = g_pipeline_sequence,
	.count = sizeof(g_pipeline_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_list_separator_sequence_with_count = {
	.name = "list separator",
	.sequence = g_list_separator_sequence,
	.count = sizeof(g_list_separator_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	*g_pipeline_or_list_separator_sequences[] = {
	&g_pipeline_sequence_with_count,
	&g_list_separator_sequence_with_count,
	NULL,
};

int	try_get_optionally_timed_or_negated_pipeline_or_list_separator(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	(void)arg;
	return (parse_recursively(current_token_node,
			syntax_tree,
			multiline_options,
			g_pipeline_or_list_separator_sequences));
}
