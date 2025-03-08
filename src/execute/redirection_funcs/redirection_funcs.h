/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_funcs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:23:56 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 14:54:05 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_FUNCS_H
# define REDIRECTION_FUNCS_H

# include <stdbool.h>
# include "../../parse/parse.h"

typedef bool	(*t_redirection_func)(
					t_redirection *redirection);

bool	perform_read_redirection(
			t_redirection *redirection);
bool	perform_read_write_redirection(
			t_redirection *redirection);
bool	perform_write_redirection(
			t_redirection *redirection);
bool	perform_append_redirection(
			t_redirection *redirection);
bool	perform_write_both_redirection(
			t_redirection *redirection);
bool	perform_append_both_redirection(
			t_redirection *redirection);
bool	perform_input_duplication(
			t_redirection *redirection);
bool	perform_output_duplication(
			t_redirection *redirection);
bool	perform_here_doc_or_string_redirection(
			t_redirection *redirection);

#endif
