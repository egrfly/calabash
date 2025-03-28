/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_positional_args_len_to_str.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:48:46 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 18:49:45 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_string.h"
#include "../../interface/interface.h"
#include "../../lex/lex.h"
#include "../escaped_string_utils/escaped_string_utils.h"

size_t	add_positional_args_len_to_str(
			int *new_str_additional_len,
			t_quote_mode quote_mode,
			t_program_vars *program_vars)
{
	size_t	i;

	i = 1;
	while (program_vars->argv[i])
	{
		if (i > 1)
			*new_str_additional_len += ft_strlen(" ");
		*new_str_additional_len += strlen_with_escapes(program_vars->argv[i],
				quote_mode == DOUBLE_QUOTED);
		i++;
	}
	*new_str_additional_len -= ft_strlen("$*");
	return (1);
}
