/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_simple_command_prefix_element.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:25:02 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 06:09:14 by emflynn          ###   ########.fr       */
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
	g_redirection_sequence[] = {
{
	.token_consumption_func = try_get_redirection,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_assignment_word_sequence[] = {
{
	.token_consumption_func = try_get_assignment_word,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = update_command_with_new_assignment,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option_sequence_with_count
	g_redirection_sequence_with_count = {
	.sequence = g_redirection_sequence,
	.count = sizeof(g_redirection_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_assignment_word_sequence_with_count = {
	.sequence = g_assignment_word_sequence,
	.count = sizeof(g_assignment_word_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	*g_simple_command_prefix_element_sequences[] = {
	&g_redirection_sequence_with_count,
	&g_assignment_word_sequence_with_count,
	NULL,
};

int	try_get_simple_command_prefix_element(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	(void)arg;
	return (parse_recursively(current_token_node,
			syntax_tree,
			multiline_options,
			g_simple_command_prefix_element_sequences));
}
