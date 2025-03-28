/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_positional_args_to_str.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:59:43 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 18:59:56 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_string.h"
#include "../../interface/interface.h"
#include "../../lex/lex.h"
#include "../escaped_string_utils/escaped_string_utils.h"

size_t	add_positional_args_to_str(
			char *new_str,
			t_quote_mode quote_mode,
			t_program_vars *program_vars)
{
	size_t	i;

	i = 1;
	while (program_vars->argv[i])
	{
		if (i > 1)
			ft_strcat(new_str, " ");
		strcat_with_escapes(new_str, program_vars->argv[i],
			quote_mode == DOUBLE_QUOTED);
		i++;
	}
	return (1);
}
