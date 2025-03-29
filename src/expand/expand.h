/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:06:20 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 19:09:48 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <stdbool.h>
# include "ft_list.h"
# include "../interface/interface.h"

# define IS_HEREDOC true
# define NOT_HEREDOC false

bool	expand_assignments(
			t_list *assignments,
			t_program_vars *program_vars);
bool	expand_arguments(
			t_list **arguments,
			t_program_vars *program_vars);
bool	expand_redirection_right_words(
			t_list *redirections,
			t_program_vars *program_vars);

#endif
