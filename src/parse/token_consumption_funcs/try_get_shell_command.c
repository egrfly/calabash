/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_get_shell_command.c                            :+:      :+:    :+:   */
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
#include "./token_consumption_funcs.h"

static const
	t_parsing_option
	g_subshell_sequence[] = {
{
	.token_consumption_func = try_get_subshell,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_group_sequence[] = {
{
	.token_consumption_func = try_get_group,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_conditional_command_sequence[] = {
{
	.token_consumption_func = try_get_conditional_command,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_arithmetic_command_sequence[] = {
{
	.token_consumption_func = try_get_arithmetic_command,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_while_command_sequence[] = {
{
	.token_consumption_func = try_get_while_command,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_until_command_sequence[] = {
{
	.token_consumption_func = try_get_until_command,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_if_command_sequence[] = {
{
	.token_consumption_func = try_get_if_command,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_for_command_sequence[] = {
{
	.token_consumption_func = try_get_for_command,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_select_command_sequence[] = {
{
	.token_consumption_func = try_get_select_command,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option
	g_case_command_sequence[] = {
{
	.token_consumption_func = try_get_case_command,
	.token_consumption_func_arg = NO_ARG,
	.tree_update_func = UPDATE_NO_OP,
	.is_optional = MANDATORY,
	.is_supported = SUPPORTED,
}};

static const
	t_parsing_option_sequence_with_count
	g_subshell_sequence_with_count = {
	.sequence = g_subshell_sequence,
	.count = sizeof(g_subshell_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_group_sequence_with_count = {
	.sequence = g_group_sequence,
	.count = sizeof(g_group_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_conditional_command_sequence_with_count = {
	.sequence = g_conditional_command_sequence,
	.count = sizeof(g_conditional_command_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_arithmetic_command_sequence_with_count = {
	.sequence = g_arithmetic_command_sequence,
	.count = sizeof(g_arithmetic_command_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_while_command_sequence_with_count = {
	.sequence = g_while_command_sequence,
	.count = sizeof(g_while_command_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_until_command_sequence_with_count = {
	.sequence = g_until_command_sequence,
	.count = sizeof(g_until_command_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_if_command_sequence_with_count = {
	.sequence = g_if_command_sequence,
	.count = sizeof(g_if_command_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_for_command_sequence_with_count = {
	.sequence = g_for_command_sequence,
	.count = sizeof(g_for_command_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_select_command_sequence_with_count = {
	.sequence = g_select_command_sequence,
	.count = sizeof(g_select_command_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	g_case_command_sequence_with_count = {
	.sequence = g_case_command_sequence,
	.count = sizeof(g_case_command_sequence)
	/ sizeof(t_parsing_option),
};

static const
	t_parsing_option_sequence_with_count
	*g_shell_command_sequences[] = {
	&g_subshell_sequence_with_count,
	&g_group_sequence_with_count,
	&g_conditional_command_sequence_with_count,
	&g_arithmetic_command_sequence_with_count,
	&g_while_command_sequence_with_count,
	&g_until_command_sequence_with_count,
	&g_if_command_sequence_with_count,
	&g_for_command_sequence_with_count,
	&g_select_command_sequence_with_count,
	&g_case_command_sequence_with_count,
	NULL,
};

int	try_get_shell_command(
		void *arg,
		t_list_node **current_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options)
{
	(void)arg;
	return (parse_recursively(current_token_node,
			syntax_tree,
			multiline_options,
			g_shell_command_sequences));
}
