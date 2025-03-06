/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:40:47 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 03:10:48 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_UTILS_H
# define COMMAND_UTILS_H

# include "../execute.h"

typedef struct s_exec_params
{
	char	*path;
	char	**args;
	char	**envp;
}	t_exec_params;

bool	init_exec_params(
			t_exec_params *exec_params,
			t_list *arguments,
			t_list *env);
void	destroy_exec_params(
			t_exec_params *exec_params);
void	exit_if_out_of_memory(
			char *program_name,
			t_exec_params *exec_params,
			t_tokens_and_syntax_tree *tokens_and_syntax_tree);
void	exit_if_command_not_found(
			char *program_name,
			char *unfound_command,
			t_exec_params *exec_params,
			t_tokens_and_syntax_tree *tokens_and_syntax_tree);
void	exit_if_execve_failed(
			char *program_name,
			char *command,
			t_exec_params *exec_params,
			t_tokens_and_syntax_tree *tokens_and_syntax_tree);

#endif
