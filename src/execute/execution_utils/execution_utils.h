/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:18:29 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 02:12:20 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_UTILS_H
# define EXECUTION_UTILS_H

# include "ft_binary_tree.h"
# include "../../interface/interface.h"
# include "../execute.h"

# define NO_OPTIONS 0

int		execute_in_child_process(
			t_execution_func execution_func,
			t_binary_tree_node *node,
			t_tokens_and_syntax_tree *tokens_and_syntax_tree,
			t_program_name_and_env *program_name_and_env);
void	destroy_tokens_and_syntax_tree(
			t_tokens_and_syntax_tree *tokens_and_syntax_tree);

#endif
