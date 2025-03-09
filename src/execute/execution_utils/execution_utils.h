/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:18:29 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/09 19:37:10 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_UTILS_H
# define EXECUTION_UTILS_H

# include "ft_binary_tree.h"
# include "../../interface/interface.h"
# include "../execute.h"

int		execute_in_child_process(
			t_execution_func execution_func,
			t_binary_tree_node *node,
			t_fixed_program_elements *fixed_program_elements,
			t_program_vars *program_vars);
void	destroy_fixed_program_elements(
			t_fixed_program_elements *fixed_program_elements);
int		try_decode_exit_status(
			int exit_status,
			int backup_exit_status);

#endif
