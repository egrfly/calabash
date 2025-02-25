/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_until_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:59:07 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/25 18:48:57 by emflynn          ###   ########.fr       */
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
	g_keyword_with_terminated_compound_list_and_body_sequence[] = {
{
	.token_consumption_func = try_get_reserved_word,
	.token_consumption_func_arg = "until",
	.tree_update_func = update_with_new_pre_command_node,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
},
{
	.token_consumption_func = try_get_multiline_whitespace,
	.token_consumption_func_arg
	= (void *)SHOULD_PROMPT_MORE_IN_INTERACTIVE_MODE,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = OPTIONAL,
	.is_supported = SUPPORTED,
},
{
	.token_consumption_func = try_get_terminated_compound_list,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func
	= update_by_moving_current_node_up_to_control_structure_node,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
},
{
	.token_consumption_func = try_get_multiline_whitespace,
	.token_consumption_func_arg
	= (void *)SHOULD_PROMPT_MORE_IN_INTERACTIVE_MODE,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = OPTIONAL,
	.is_supported = SUPPORTED,
},
{
	.token_consumption_func = try_get_loop_command_body,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = update_by_closing_previous_pre_command_node,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option_sequence_with_count
	g_keyword_with_terminated_compound_list_and_body_sequence_with_count = {
	.sequence
	= g_keyword_with_terminated_compound_list_and_body_sequence,
	.count = sizeof(g_keyword_with_terminated_compound_list_and_body_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	*g_until_command_sequences[] = {
	&g_keyword_with_terminated_compound_list_and_body_sequence_with_count,
	NULL,
};

int	try_get_until_command(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	(void)arg;
	return (parse_recursively(current_token_node,
			syntax_tree,
			multiline_options,
			g_until_command_sequences));
}
