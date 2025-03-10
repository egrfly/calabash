/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:40:31 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 05:57:07 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "ft_binary_tree.h"
# include "ft_list.h"
# include "../lex/lex.h"
# include "../interface/interface.h"
# include "../parse/parse.h"
# include "./pipeline_lifecycle/pipeline_lifecycle.h"

typedef struct s_tokens_and_syntax_tree
{
	t_list					*tokens;
	t_syntax_tree			*syntax_tree;
}	t_tokens_and_syntax_tree;

typedef int	(*t_execution_func)(
	t_binary_tree_node *node,
	t_tokens_and_syntax_tree *tokens_and_syntax_tree,
	t_program_vars *program_vars);

int	execute(
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars);
int	execute_recursively(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars);

#endif
