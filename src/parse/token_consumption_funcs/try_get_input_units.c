/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_input_units.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:06:12 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 14:10:02 by emflynn          ###   ########.fr       */
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
	g_sync_or_async_simple_command_lists_sequence[] = {
{
	.token_consumption_func = try_get_sync_or_async_simple_command_list,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
},
{
	.token_consumption_func = try_get_input_units_continuation,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = OPTIONAL,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option_sequence_with_count
	g_sync_or_async_simple_command_lists_sequence_with_count = {
	.name = "sync or async simple command lists",
	.sequence = g_sync_or_async_simple_command_lists_sequence,
	.count = sizeof(g_sync_or_async_simple_command_lists_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	*g_input_units_sequences[] = {
	&g_sync_or_async_simple_command_lists_sequence_with_count,
	NULL,
};

int	try_get_input_units(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	(void)arg;
	return (parse_recursively(current_token_node,
			syntax_tree,
			multiline_options,
			g_input_units_sequences));
}
