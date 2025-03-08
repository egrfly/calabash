/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_group.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:24:48 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 09:03:56 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_tree.h"
#include "../../interface/interface.h"
#include "../execute.h"

// TODO: these can have redirections
int	execute_group(
		t_binary_tree_node *node,
		t_fixed_program_elements *fixed_program_elements,
		t_program_vars *program_vars)
{
	return (execute_recursively(node->primary_child, fixed_program_elements,
			program_vars));
}
