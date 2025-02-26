/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_named_or_unnamed_coprocess_declarat        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:59:07 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 14:25:29 by emflynn          ###   ########.fr       */
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
	g_named_coprocess_declaration_sequence[] = {
{
	.token_consumption_func = try_get_named_coprocess_declaration,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_unnamed_coprocess_declaration_sequence[] = {
{
	.token_consumption_func = try_get_unnamed_coprocess_declaration,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option_sequence_with_count
	g_named_coprocess_declaration_sequence_with_count = {
	.name = "named coprocess declaration",
	.sequence = g_named_coprocess_declaration_sequence,
	.count = sizeof(g_named_coprocess_declaration_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_unnamed_coprocess_declaration_sequence_with_count = {
	.name = "unnamed coprocess declaration",
	.sequence = g_unnamed_coprocess_declaration_sequence,
	.count = sizeof(g_unnamed_coprocess_declaration_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	*g_coprocess_sequences[] = {
	&g_named_coprocess_declaration_sequence_with_count,
	&g_unnamed_coprocess_declaration_sequence_with_count,
	NULL,
};

int	try_get_named_or_unnamed_coprocess_declaration(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	(void)arg;
	return (parse_recursively(current_token_node,
			syntax_tree,
			multiline_options,
			g_coprocess_sequences));
}
