/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:06:20 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/26 17:46:53 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <stdbool.h>
# include "ft_list.h"
# include "../interface/interface.h"
# include "../parse/parse.h"

# define IS_HEREDOC true
# define NOT_HEREDOC false

bool	expand_assignment(
			t_list_node *assignment_node,
			t_program_vars *program_vars);
bool	expand_assignments(
			t_list *assignments,
			t_program_vars *program_vars);
bool	expand_arguments(
			t_list **arguments,
			t_program_vars *program_vars);
bool	expand_redirection_right_word(
			t_redirection *redirection,
			t_program_vars *program_vars);
bool	expand_redirection_right_words(
			t_list *redirections,
			t_program_vars *program_vars);

#endif
