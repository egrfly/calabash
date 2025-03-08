/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_redirection_operator_without_ampers        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:25:02 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 12:40:59 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "../../interface/interface.h"
#include "../../lex/lex.h"
#include "../parse.h"
#include "../parsing_utils/parsing_utils.h"
#include "../tree_update_funcs/tree_update_funcs.h"
#include "./token_consumption_funcs.h"

static const
	t_parsing_option
	g_here_string_operator_sequence[] = {
{
	.token_consumption_func = try_get_operator,
	.token_consumption_func_arg = (void *)LESS_LESS_LESS,
	.tree_update_func = update_command_with_new_redirection_operator,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_indented_here_doc_operator_sequence[] = {
{
	.token_consumption_func = try_get_operator,
	.token_consumption_func_arg = (void *)LESS_LESS_DASH,
	.tree_update_func = update_command_with_new_redirection_operator,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_here_doc_operator_sequence[] = {
{
	.token_consumption_func = try_get_operator,
	.token_consumption_func_arg = (void *)LESS_LESS,
	.tree_update_func = update_command_with_new_redirection_operator,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_read_write_operator_sequence[] = {
{
	.token_consumption_func = try_get_operator,
	.token_consumption_func_arg = (void *)LESS_GREATER,
	.tree_update_func = update_command_with_new_redirection_operator,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_read_operator_sequence[] = {
{
	.token_consumption_func = try_get_operator,
	.token_consumption_func_arg = (void *)LESS,
	.tree_update_func = update_command_with_new_redirection_operator,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_append_operator_sequence[] = {
{
	.token_consumption_func = try_get_operator,
	.token_consumption_func_arg = (void *)GREATER_GREATER,
	.tree_update_func = update_command_with_new_redirection_operator,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_force_write_operator_sequence[] = {
{
	.token_consumption_func = try_get_operator,
	.token_consumption_func_arg = (void *)GREATER_BAR,
	.tree_update_func = update_command_with_new_redirection_operator,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_write_operator_sequence[] = {
{
	.token_consumption_func = try_get_operator,
	.token_consumption_func_arg = (void *)GREATER,
	.tree_update_func = update_command_with_new_redirection_operator,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option_sequence_with_count
	g_here_string_operator_sequence_with_count = {
	.name = "here string operator",
	.sequence = g_here_string_operator_sequence,
	.count = sizeof(g_here_string_operator_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_indented_here_doc_operator_sequence_with_count = {
	.name = "indented here doc operator",
	.sequence = g_indented_here_doc_operator_sequence,
	.count = sizeof(g_indented_here_doc_operator_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_here_doc_operator_sequence_with_count = {
	.name = "here doc operator",
	.sequence = g_here_doc_operator_sequence,
	.count = sizeof(g_here_doc_operator_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_read_write_operator_sequence_with_count = {
	.name = "read write operator",
	.sequence = g_read_write_operator_sequence,
	.count = sizeof(g_read_write_operator_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_read_operator_sequence_with_count = {
	.name = "read operator",
	.sequence = g_read_operator_sequence,
	.count = sizeof(g_read_operator_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_append_operator_sequence_with_count = {
	.name = "append operator",
	.sequence = g_append_operator_sequence,
	.count = sizeof(g_append_operator_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_force_write_operator_sequence_with_count = {
	.name = "force write operator",
	.sequence = g_force_write_operator_sequence,
	.count = sizeof(g_force_write_operator_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_write_operator_sequence_with_count = {
	.name = "write operator",
	.sequence = g_write_operator_sequence,
	.count = sizeof(g_write_operator_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	*g_redirection_symbol_without_ampersand_sequences[] = {
	&g_here_string_operator_sequence_with_count,
	&g_indented_here_doc_operator_sequence_with_count,
	&g_here_doc_operator_sequence_with_count,
	&g_read_write_operator_sequence_with_count,
	&g_read_operator_sequence_with_count,
	&g_append_operator_sequence_with_count,
	&g_force_write_operator_sequence_with_count,
	&g_write_operator_sequence_with_count,
	NULL,
};

int	try_get_redirection_operator_without_ampersand(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	(void)arg;
	return (parse_recursively(current_token_node,
			syntax_tree,
			multiline_options,
			g_redirection_symbol_without_ampersand_sequences));
}
