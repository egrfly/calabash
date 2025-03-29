/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_single_digit_positional_arg_to_str.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:02:14 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 19:02:42 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../interface/interface.h"
#include "../../lex/lex.h"
#include "../escaped_string_utils/escaped_string_utils.h"

size_t	add_single_digit_positional_arg_to_str(
			char *original_str,
			char *new_str,
			t_quote_mode quote_mode,
			t_program_vars *program_vars)
{
	if (*original_str - '0' < program_vars->argc)
		strcat_with_escapes(new_str, program_vars->argv[*original_str - '0'],
			quote_mode == DOUBLE_QUOTED);
	return (1);
}
