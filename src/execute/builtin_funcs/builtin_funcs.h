/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funcs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:14:06 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 21:56:55 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_FUNCS_H
# define BUILTIN_FUNCS_H

# include "ft_binary_tree.h"
# include "../../interface/interface.h"
# include "../execute.h"

int	builtin_env(
		t_binary_tree_node *node,
		t_fixed_program_elements *fixed_program_elements,
		t_program_vars *program_vars);
int	builtin_export(
		t_binary_tree_node *node,
		t_fixed_program_elements *fixed_program_elements,
		t_program_vars *program_vars);
int	builtin_unset(
		t_binary_tree_node *node,
		t_fixed_program_elements *fixed_program_elements,
		t_program_vars *program_vars);

#endif
