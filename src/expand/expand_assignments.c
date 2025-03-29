/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_assignments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:08:06 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/29 18:33:57 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../interface/interface.h"
#include "./expand.h"
#include "./expand_tildes/expand_tildes.h"
#include "./expand_variables/expand_variables.h"
#include "./remove_quoting/remove_quoting.h"

static bool	expand_assignment(
				t_list_node *assignment_node,
				t_program_vars *program_vars)
{
	if (!expand_tildes((char **)&assignment_node->value, program_vars)
		|| !expand_variables((char **)&assignment_node->value, program_vars,
			NOT_HEREDOC))
		return (false);
	remove_quoting(assignment_node->value, NOT_HEREDOC);
	return (true);
}

bool	expand_assignments(
			t_list *assignments,
			t_program_vars *program_vars)
{
	t_list_node	*assignment_node;

	assignment_node = assignments->first;
	while (assignment_node)
	{
		if (!expand_assignment(assignment_node, program_vars))
			return (false);
		assignment_node = assignment_node->next;
	}
	return (true);
}
