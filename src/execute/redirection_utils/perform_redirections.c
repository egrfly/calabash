/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:31:37 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/29 21:51:20 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_list.h"
#include "../../lex/lex.h"
#include "../../parse/parse.h"
#include "../redirection_funcs/redirection_funcs.h"
#include "./redirection_utils.h"

static const
	t_redirection_func
	g_redirection_funcs[] = {
[AMPERSAND_GREATER_GREATER] = perform_append_both_redirection,
[AMPERSAND_GREATER] = perform_write_both_redirection,
[LESS_LESS_LESS] = perform_here_doc_or_string_redirection,
[LESS_LESS_DASH] = perform_here_doc_or_string_redirection,
[LESS_LESS] = perform_here_doc_or_string_redirection,
[LESS_GREATER] = perform_read_write_redirection,
[LESS_AMPERSAND] = perform_input_duplication,
[LESS] = perform_read_redirection,
[GREATER_GREATER] = perform_append_redirection,
[GREATER_BAR] = perform_write_redirection,
[GREATER_AMPERSAND] = perform_output_duplication,
[GREATER] = perform_write_redirection,
};

static bool	perform_redirection(
				t_redirection *redirection)
{
	t_redirection_func	redirection_func;

	redirection_func = g_redirection_funcs[redirection->operator];
	if (redirection_func)
		return (redirection_func(redirection));
	return (false);
}

bool	perform_redirections(
			t_list *redirections)
{
	t_list_node		*current_redirection_node;
	t_redirection	*current_redirection;

	if (!redirections)
		return (true);
	current_redirection_node = redirections->first;
	while (current_redirection_node)
	{
		current_redirection = current_redirection_node->value;
		if (!perform_redirection(current_redirection))
		{
			revert_redirections(redirections);
			return (false);
		}
		current_redirection_node = current_redirection_node->next;
	}
	return (true);
}
