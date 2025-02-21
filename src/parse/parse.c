/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:13:15 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 06:28:47 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "../interface/interface.h"
#include "./parse.h"
#include "./parsing_utils/parsing_utils.h"
#include "./token_consumption_funcs/token_consumption_funcs.h"
#include "./tree_lifecycle/tree_lifecycle.h"

static const
	t_parsing_option
	g_input_units_and_end_of_input_sequence[] = {
{
	.token_consumption_func = try_get_multiline_whitespace,
	.token_consumption_func_arg
	= (void *)SHOULD_NOT_PROMPT_FURTHER_IN_INTERACTIVE_MODE,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = OPTIONAL,
	.is_supported = SUPPORTED,
},
{
	.token_consumption_func = try_get_input_units,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = OPTIONAL,
	.is_supported = SUPPORTED,
},
{
	.token_consumption_func = try_get_multiline_whitespace,
	.token_consumption_func_arg
	= (void *)SHOULD_NOT_PROMPT_FURTHER_IN_INTERACTIVE_MODE,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = OPTIONAL,
	.is_supported = SUPPORTED,
},
{
	.token_consumption_func = try_get_end_of_input,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option_sequence_with_count
	g_input_units_and_end_of_input_sequence_with_count = {
	.sequence = g_input_units_and_end_of_input_sequence,
	.count = sizeof(g_input_units_and_end_of_input_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	*g_top_level_sequences[] = {
	&g_input_units_and_end_of_input_sequence_with_count,
	NULL,
};

t_syntax_tree	*parse(
					t_list *tokens,
					t_multiline_options *multiline_options)
{
	t_list_node		*current_token_node;
	t_syntax_tree	*syntax_tree;

	current_token_node = tokens->first;
	syntax_tree = create_syntax_tree();
	if (!syntax_tree)
		return (NULL);
	if (!parse_recursively(&current_token_node,
			syntax_tree,
			multiline_options,
			g_top_level_sequences))
		syntax_tree->some_tokens_left_unconsumed = true;
	return (syntax_tree);
}
