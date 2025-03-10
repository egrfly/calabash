/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:40:47 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 11:57:01 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_UTILS_H
# define COMMAND_UTILS_H

# include "ft_list.h"
# include "../../interface/interface.h"
# include "../execute.h"

typedef struct s_exec_params
{
	char	*command;
	char	*path;
	char	**args;
	char	**envp;
}	t_exec_params;

bool	init_exec_params(
			t_exec_params *exec_params,
			t_list *arguments,
			t_list *assignments,
			t_list *vars);
void	destroy_exec_params(
			t_exec_params *exec_params);
void	exit_due_to_lack_of_memory(
			t_program_vars *program_vars,
			t_exec_params *exec_params,
			t_tokens_and_syntax_tree *tokens_and_syntax_tree);
void	exit_due_to_redirection_failure(
			t_program_vars *program_vars,
			t_exec_params *exec_params,
			t_tokens_and_syntax_tree *tokens_and_syntax_tree);
void	exit_due_to_unfound_command(
			t_program_vars *program_vars,
			t_exec_params *exec_params,
			t_tokens_and_syntax_tree *tokens_and_syntax_tree,
			t_list *redirections);
void	exit_due_to_execve_failure(
			t_program_vars *program_vars,
			t_exec_params *exec_params,
			t_tokens_and_syntax_tree *tokens_and_syntax_tree,
			t_list *redirections);

#endif
