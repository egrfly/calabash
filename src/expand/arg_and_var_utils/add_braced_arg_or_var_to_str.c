/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_braced_arg_or_var_to_str.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:04:04 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/28 19:51:30 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ctype.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "../../execute/var_utils/var_utils.h"
#include "../../interface/interface.h"
#include "../../lex/lex.h"
#include "../char_utils/char_utils.h"
#include "../escaped_string_utils/escaped_string_utils.h"

size_t	add_braced_arg_or_var_to_str(
			char *original_str,
			char *new_str,
			t_quote_mode quote_mode,
			t_program_vars *program_vars)
{
	size_t	i;
	size_t	j;
	char	*var_value;
	int		nbr;

	i = 1;
	j = ft_strcspn(&original_str[i], "}");
	if (isalpha_or_underscore(original_str[i])
		&& ft_strnall(&original_str[i + 1], isalnum_or_underscore, j - 1))
	{
		var_value = get_var_value_n(&original_str[i], j, program_vars->vars);
		if (var_value)
			strcat_with_escapes(new_str, var_value,
				quote_mode == DOUBLE_QUOTED);
	}
	else if (ft_strnall(&original_str[i], ft_isdigit, j)
		&& ft_strntoi(&original_str[i], &nbr, j) && nbr < program_vars->argc)
		strcat_with_escapes(new_str, program_vars->argv[nbr],
			quote_mode == DOUBLE_QUOTED);
	i += j + 1;
	return (i);
}
