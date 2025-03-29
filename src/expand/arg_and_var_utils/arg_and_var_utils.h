/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_and_var_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:48:00 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 19:49:35 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARG_AND_VAR_UTILS_H
# define ARG_AND_VAR_UTILS_H

# include <stdlib.h>
# include "../../interface/interface.h"
# include "../../lex/lex.h"

size_t	add_positional_args_len_to_str(
			int *new_str_additional_len,
			t_quote_mode quote_mode,
			t_program_vars *program_vars);
size_t	add_arg_count_len_to_str(
			int *new_str_additional_len,
			t_program_vars *program_vars);
size_t	add_last_exit_code_len_to_str(
			int *new_str_additional_len,
			t_program_vars *program_vars);
size_t	add_single_digit_positional_arg_len_to_str(
			char *original_str,
			int *new_str_additional_len,
			t_quote_mode quote_mode,
			t_program_vars *program_vars);
size_t	add_unbraced_env_var_len_to_str(
			char *original_str,
			int *new_str_additional_len,
			t_quote_mode quote_mode,
			t_program_vars *program_vars);
size_t	add_braced_arg_or_var_len_to_str(
			char *original_str,
			int *new_str_additional_len,
			t_quote_mode quote_mode,
			t_program_vars *program_vars);
size_t	add_positional_args_to_str(
			char *new_str,
			t_quote_mode quote_mode,
			t_program_vars *program_vars);
size_t	add_arg_count_to_str(
			char *new_str,
			t_program_vars *program_vars);
size_t	add_last_exit_code_to_str(
			char *new_str,
			t_program_vars *program_vars);
size_t	add_single_digit_positional_arg_to_str(
			char *original_str,
			char *new_str,
			t_quote_mode quote_mode,
			t_program_vars *program_vars);
size_t	add_unbraced_env_var_to_str(
			char *original_str,
			char *new_str,
			t_quote_mode quote_mode,
			t_program_vars *program_vars);
size_t	add_braced_arg_or_var_to_str(
			char *original_str,
			char *new_str,
			t_quote_mode quote_mode,
			t_program_vars *program_vars);

#endif
