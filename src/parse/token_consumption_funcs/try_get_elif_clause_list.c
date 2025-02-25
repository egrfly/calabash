/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_elif_clause_list.c                         :+:      :+:    :+:   */
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
#include "./token_consumption_funcs.h"

static const
	t_parsing_option
	g_elif_clause_with_elif_clause_list_sequence[] = {
{
	.token_consumption_func = try_get_elif_clause,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
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
	.token_consumption_func = try_get_elif_clause_list,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = OPTIONAL,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option_sequence_with_count
	g_elif_clause_with_elif_clause_list_sequence_with_count = {
	.sequence = g_elif_clause_with_elif_clause_list_sequence,
	.count = sizeof(g_elif_clause_with_elif_clause_list_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	*g_elif_clause_list_sequences[] = {
	&g_elif_clause_with_elif_clause_list_sequence_with_count,
	NULL,
};

int	try_get_elif_clause_list(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	(void)arg;
	return (parse_recursively(current_token_node,
			syntax_tree,
			multiline_options,
			g_elif_clause_list_sequences));
}
