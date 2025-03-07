/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:40:31 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/07 08:46:44 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "ft_binary_tree.h"
# include "../lex/lex.h"
# include "../interface/interface.h"
# include "../parse/parse.h"

typedef struct s_tokens_and_syntax_tree
{
	t_tokens_with_status	*tokens_with_status;
	t_syntax_tree			*syntax_tree;
	t_multiline_options		*multiline_options;
}	t_tokens_and_syntax_tree;

typedef int	(*t_execution_func)(
	t_binary_tree_node *node,
	t_tokens_and_syntax_tree *tokens_and_syntax_tree,
	t_program_name_and_env *program_name_and_env);

int	execute(
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_name_and_env *program_name_and_env);
int	execute_recursively(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_name_and_env *program_name_and_env);
int	execute_builtin_command(
		const char *command, const char **argv,
		t_program_name_and_env *program_name_and_env);

#endif
