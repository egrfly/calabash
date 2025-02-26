/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_simple_command_list.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:16:23 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 14:44:47 by emflynn          ###   ########.fr       */
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
	g_optionally_timed_or_negated_pipelines_sequence[] = {
{
	.token_consumption_func = try_get_optionally_timed_or_negated_pipeline,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
},
{
	.token_consumption_func = try_get_single_line_whitespace,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = OPTIONAL,
	.is_supported = SUPPORTED,
},
{
	.token_consumption_func = try_get_simple_command_list_continuation,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = OPTIONAL,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option_sequence_with_count
	g_optionally_timed_or_negated_pipelines_sequence_with_count = {
	.name = "optionally timed or negated pipelines",
	.sequence = g_optionally_timed_or_negated_pipelines_sequence,
	.count = sizeof(g_optionally_timed_or_negated_pipelines_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	*g_simple_command_list_sequences[] = {
	&g_optionally_timed_or_negated_pipelines_sequence_with_count,
	NULL,
};

int	try_get_simple_command_list(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	(void)arg;
	return (parse_recursively(current_token_node,
			syntax_tree,
			multiline_options,
			g_simple_command_list_sequences));
}
