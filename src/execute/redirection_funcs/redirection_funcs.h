/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_funcs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:23:56 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 08:15:02 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_FUNCS_H
# define REDIRECTION_FUNCS_H

# include <stdbool.h>
# include "../../parse/parse.h"

typedef bool	(*t_redirection_func)(
					t_redirection *redirection,
					char *program_name);

bool	perform_read_redirection(
			t_redirection *redirection,
			char *program_name);
bool	perform_read_write_redirection(
			t_redirection *redirection,
			char *program_name);
bool	perform_write_redirection(
			t_redirection *redirection,
			char *program_name);
bool	perform_append_redirection(
			t_redirection *redirection,
			char *program_name);
bool	perform_write_both_redirection(
			t_redirection *redirection,
			char *program_name);
bool	perform_append_both_redirection(
			t_redirection *redirection,
			char *program_name);
bool	perform_input_duplication(
			t_redirection *redirection,
			char *program_name);
bool	perform_output_duplication(
			t_redirection *redirection,
			char *program_name);

#endif
