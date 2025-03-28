/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_single_digit_positional_arg_len_to_str.        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:53:37 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 18:53:55 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_string.h"
#include "../../interface/interface.h"
#include "../../lex/lex.h"
#include "../escaped_string_utils/escaped_string_utils.h"

size_t	add_single_digit_positional_arg_len_to_str(
			char *original_str,
			int *new_str_additional_len,
			t_quote_mode quote_mode,
			t_program_vars *program_vars)
{
	if (*original_str - '0' < program_vars->argc)
		*new_str_additional_len += strlen_with_escapes(
				program_vars->argv[*original_str - '0'],
				quote_mode == DOUBLE_QUOTED);
	*new_str_additional_len -= ft_strlen("$") + 1;
	return (1);
}
